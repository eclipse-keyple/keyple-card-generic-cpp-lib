/******************************************************************************
 * Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/    *
 *                                                                            *
 * See the NOTICE file(s) distributed with this work for additional           *
 * information regarding copyright ownership.                                 *
 *                                                                            *
 * This program and the accompanying materials are made available under the   *
 * terms of the Eclipse Public License 2.0 which is available at              *
 * http://www.eclipse.org/legal/epl-2.0                                       *
 *                                                                            *
 * SPDX-License-Identifier: EPL-2.0                                           *
 ******************************************************************************/

#include "keyple/card/generic/CardTransactionManagerAdapter.hpp"

#include "keyple/card/generic/ApduRequestAdapter.hpp"
#include "keyple/card/generic/CardRequestAdapter.hpp"
#include "keyple/card/generic/ChannelControl.hpp"
#include "keyple/card/generic/TransactionException.hpp"
#include "keyple/core/util/ApduUtil.hpp"
#include "keyple/core/util/ByteArrayUtil.hpp"
#include "keyple/core/util/HexUtil.hpp"
#include "keyple/core/util/KeypleAssert.hpp"
#include "keypop/card/CardBrokenCommunicationException.hpp"
#include "keypop/card/CardResponseApi.hpp"
#include "keypop/card/ProxyReaderApi.hpp"
#include "keypop/card/ReaderBrokenCommunicationException.hpp"
#include "keypop/card/UnexpectedStatusWordException.hpp"

namespace keyple {
namespace card {
namespace generic {

using keyple::core::util::ApduUtil;
using keyple::core::util::Assert;
using keyple::core::util::ByteArrayUtil;
using keyple::core::util::HexUtil;
using keypop::card::CardBrokenCommunicationException;
using keypop::card::CardResponseApi;
using keypop::card::ProxyReaderApi;
using keypop::card::ReaderBrokenCommunicationException;
using keypop::card::UnexpectedStatusWordException;

const std::string CardTransactionManagerAdapter::APDU_COMMAND = "apduCommand";

CardTransactionManagerAdapter::CardTransactionManagerAdapter(
    std::shared_ptr<CardReader> reader, const std::shared_ptr<SmartCard> card)
: mReader(reader)
{
    Assert::getInstance().notNull(reader, "reader").notNull(card, "card");
}

CardTransactionManager&
CardTransactionManagerAdapter::prepareApdu(const std::string& apduCommand)
{
    Assert::getInstance()
        .notEmpty(apduCommand, APDU_COMMAND)
        .isTrue(HexUtil::isValid(apduCommand), APDU_COMMAND);

    prepareApdu(HexUtil::toByteArray(apduCommand));

    return *this;
}

CardTransactionManager&
CardTransactionManagerAdapter::prepareApdu(
    const std::vector<uint8_t>& apduCommand)
{
    Assert::getInstance().isInRange(
        static_cast<int>(apduCommand.size()), 5, 251, "length");

    mApduRequests.push_back(std::make_shared<ApduRequestAdapter>(apduCommand));

    return *this;
}

CardTransactionManager&
CardTransactionManagerAdapter::prepareApdu(
    const uint8_t cla,
    const uint8_t ins,
    const uint8_t p1,
    const uint8_t p2,
    const std::vector<uint8_t>& dataIn,
    const uint8_t le)
{
    mApduRequests.push_back(std::make_shared<ApduRequestAdapter>(
        ApduUtil::build(cla, ins, p1, p2, dataIn, le)));

    return *this;
}

CardTransactionManager&
CardTransactionManagerAdapter::prepareApdu(
    const uint8_t cla,
    const uint8_t ins,
    const uint8_t p1,
    const uint8_t p2,
    const std::vector<uint8_t>& dataIn)
{
    mApduRequests.push_back(std::make_shared<ApduRequestAdapter>(
        ApduUtil::build(cla, ins, p1, p2, dataIn)));

    return *this;
}

const std::vector<std::vector<uint8_t>>
CardTransactionManagerAdapter::processApdusToByteArrays(
    const ChannelControl channelControl)
{
    std::shared_ptr<CardResponseApi> cardResponse;
    std::vector<std::vector<uint8_t>> apduResponsesBytes;

    if (mApduRequests.empty()) {
        return apduResponsesBytes;
    }

    try {
        auto cardRequest
            = std::make_shared<CardRequestAdapter>(mApduRequests, false);
        auto control = channelControl == ChannelControl::CLOSE_AFTER
                           ? keypop::card::ChannelControl::CLOSE_AFTER
                           : keypop::card::ChannelControl::KEEP_OPEN;

        cardResponse = std::dynamic_pointer_cast<ProxyReaderApi>(mReader)
                           ->transmitCardRequest(cardRequest, control);

    } catch (const ReaderBrokenCommunicationException& e) {
        throw TransactionException(
            "Reader communication error",
            std::make_shared<ReaderBrokenCommunicationException>(e));
    } catch (const CardBrokenCommunicationException& e) {
        throw TransactionException(
            "Card communication error",
            std::make_shared<CardBrokenCommunicationException>(e));
    } catch (const UnexpectedStatusWordException& e) {
        throw TransactionException(
            "Apdu error", std::make_shared<UnexpectedStatusWordException>(e));
    }

    mApduRequests.clear();

    for (const auto& apduResponse : cardResponse->getApduResponses()) {
        apduResponsesBytes.push_back(apduResponse->getApdu());
    }

    return apduResponsesBytes;
}

const std::vector<std::string>
CardTransactionManagerAdapter::processApdusToHexStrings(
    const ChannelControl channelControl)
{
    std::vector<std::string> apduResponsesHex;
    const std::vector<std::vector<uint8_t>> apduResponsesBytes
        = processApdusToByteArrays(channelControl);

    for (const auto& bytes : apduResponsesBytes) {
        apduResponsesHex.push_back(HexUtil::toHex(bytes));
    }

    return apduResponsesHex;
}

} /* namespace generic */
} /* namespace card */
} /* namespace keyple */
