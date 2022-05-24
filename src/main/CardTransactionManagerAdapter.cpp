/**************************************************************************************************
 * Copyright (c) 2021 Calypso Networks Association https://calypsonet.org/                        *
 *                                                                                                *
 * See the NOTICE file(s) distributed with this work for additional information regarding         *
 * copyright ownership.                                                                           *
 *                                                                                                *
 * This program and the accompanying materials are made available under the terms of the Eclipse  *
 * Public License 2.0 which is available at http://www.eclipse.org/legal/epl-2.0                  *
 *                                                                                                *
 * SPDX-License-Identifier: EPL-2.0                                                               *
 **************************************************************************************************/

#include "CardTransactionManagerAdapter.h"

/* Keyple Core Util */
#include "ApduUtil.h"
#include "ByteArrayUtil.h"
#include "KeypleAssert.h"

/* Keyple Card Generic */
#include "ApduRequestAdapter.h"
#include "TransactionException.h"

/* Calypsonet Terminal Card */
#include "CardBrokenCommunicationException.h"
#include "CardRequestAdapter.h"
#include "CardResponseApi.h"
#include "ProxyReaderApi.h"
#include "ReaderBrokenCommunicationException.h"
#include "UnexpectedStatusWordException.h"

namespace keyple {
namespace card {
namespace generic {

using namespace calypsonet::terminal::card;
using namespace keyple::core::util;

const std::string CardTransactionManagerAdapter::APDU_COMMAND = "apduCommand";

CardTransactionManagerAdapter::CardTransactionManagerAdapter(std::shared_ptr<CardReader> reader,
                                                             const std::shared_ptr<SmartCard> card)
: mReader(reader), mChannelControl(ChannelControl::KEEP_OPEN)
{
    Assert::getInstance().notNull(reader, "reader").notNull(card, "card");
}

CardTransactionManager& CardTransactionManagerAdapter::prepareApdu(const std::string& apduCommand)
{
    Assert::getInstance().notEmpty(apduCommand, APDU_COMMAND)
                         .isTrue(ByteArrayUtil::isValidHexString(apduCommand), APDU_COMMAND);

    prepareApdu(ByteArrayUtil::fromHex(apduCommand));

    return *this;
}

CardTransactionManager& CardTransactionManagerAdapter::prepareApdu(
    const std::vector<uint8_t>& apduCommand)
{
    Assert::getInstance().isInRange(static_cast<int>(apduCommand.size()), 5, 251, "length");

    mApduRequests.push_back(std::make_shared<ApduRequestAdapter>(apduCommand));

    return *this;
}

CardTransactionManager& CardTransactionManagerAdapter::prepareApdu(
    const uint8_t cla,
    const uint8_t ins,
    const uint8_t p1,
    const uint8_t p2,
    const std::vector<uint8_t>& dataIn,
    const uint8_t le)
{
    mApduRequests.push_back(
        std::make_shared<ApduRequestAdapter>(ApduUtil::build(cla, ins, p1, p2, dataIn, le)));

    return *this;
}

CardTransactionManager& CardTransactionManagerAdapter::prepareApdu(
    const uint8_t cla,
    const uint8_t ins,
    const uint8_t p1,
    const uint8_t p2,
    const std::vector<uint8_t>& dataIn)
{
    mApduRequests.push_back(
        std::make_shared<ApduRequestAdapter>(ApduUtil::build(cla, ins, p1, p2, dataIn)));

    return *this;
}

CardTransactionManager& CardTransactionManagerAdapter::prepareReleaseChannel()
{
    mChannelControl = ChannelControl::CLOSE_AFTER;

    return *this;
}

const std::vector<std::vector<uint8_t>> CardTransactionManagerAdapter::processApdusToByteArrays()
{
    std::shared_ptr<CardResponseApi> cardResponse;
    std::vector<std::vector<uint8_t>> apduResponsesBytes;

    if (mApduRequests.empty()) {
        return apduResponsesBytes;
    }

    try {
        cardResponse =
            std::dynamic_pointer_cast<ProxyReaderApi>(mReader)
                ->transmitCardRequest(
                    std::make_shared<CardRequestAdapter>(mApduRequests, false), mChannelControl);

    } catch (const ReaderBrokenCommunicationException& e) {
        throw TransactionException("Reader communication error.",
                                   std::make_shared<ReaderBrokenCommunicationException>(e));
    } catch (const CardBrokenCommunicationException& e) {
        throw TransactionException("Card communication error.",
                                   std::make_shared<CardBrokenCommunicationException>(e));
    } catch (const UnexpectedStatusWordException& e) {
        throw TransactionException("Apdu error.",
                                   std::make_shared<UnexpectedStatusWordException>(e));
    }

    mApduRequests.clear();

    for (const auto& apduResponse : cardResponse->getApduResponses()) {
        apduResponsesBytes.push_back(apduResponse->getApdu());
    }

    return apduResponsesBytes;
}

const std::vector<std::string> CardTransactionManagerAdapter::processApdusToHexStrings()
{
    const std::vector<std::vector<uint8_t>> apduResponsesBytes = processApdusToByteArrays();
    std::vector<std::string> apduResponsesHex;

    for (const auto& bytes : apduResponsesBytes) {
        apduResponsesHex.push_back(ByteArrayUtil::toHex(bytes));
    }

    return apduResponsesHex;
}

}
}
}
