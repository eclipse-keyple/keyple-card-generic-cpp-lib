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

#include <memory>
#include <string>
#include <vector>

#include "keyple/card/generic/ApduRequestAdapter.hpp"
#include "keyple/card/generic/CardRequestAdapter.hpp"
#include "keyple/core/util/ApduUtil.hpp"
#include "keyple/core/util/ByteArrayUtil.hpp"
#include "keyple/core/util/HexUtil.hpp"
#include "keyple/core/util/KeypleAssert.hpp"
#include "keyple/core/util/cpp/exception/Exception.hpp"
#include "keypop/card/CardBrokenCommunicationException.hpp"
#include "keypop/card/CardResponseApi.hpp"
#include "keypop/card/ChannelControl.hpp"
#include "keypop/card/ProxyReaderApi.hpp"
#include "keypop/card/ReaderBrokenCommunicationException.hpp"
#include "keypop/card/UnexpectedStatusWordException.hpp"
#include "keypop/reader/CardCommunicationException.hpp"
#include "keypop/reader/InvalidCardResponseException.hpp"
#include "keypop/reader/ReaderCommunicationException.hpp"

namespace keyple {
namespace card {
namespace generic {

using keyple::core::util::ApduUtil;
using keyple::core::util::Assert;
using keyple::core::util::ByteArrayUtil;
using keyple::core::util::HexUtil;
using keyple::core::util::cpp::exception::Exception;
using keypop::card::CardBrokenCommunicationException;
using keypop::card::CardResponseApi;
using keypop::card::ProxyReaderApi;
using keypop::card::ReaderBrokenCommunicationException;
using keypop::card::UnexpectedStatusWordException;
using keypop::reader::CardCommunicationException;
using keypop::reader::InvalidCardResponseException;
using keypop::reader::ReaderCommunicationException;

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
        static_cast<int>(apduCommand.size()), 5, 261, "length");

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
    mApduRequests.push_back(
        std::make_shared<ApduRequestAdapter>(
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
    mApduRequests.push_back(
        std::make_shared<ApduRequestAdapter>(
            ApduUtil::build(cla, ins, p1, p2, dataIn)));

    return *this;
}

CardTransactionManager&
CardTransactionManagerAdapter::processCommands(
    const ChannelControl channelControl)
{
    mApduResponses.clear();

    if (mApduRequests.empty()) {
        return *this;
    }

    std::shared_ptr<CardResponseApi> cardResponse;

    try {
        auto cardRequest
            = std::make_shared<CardRequestAdapter>(mApduRequests, false);
        auto control = channelControl == ChannelControl::CLOSE_AFTER
                           ? keypop::card::ChannelControl::CLOSE_AFTER
                           : keypop::card::ChannelControl::KEEP_OPEN;

        cardResponse = std::dynamic_pointer_cast<ProxyReaderApi>(mReader)
                           ->transmitCardRequest(cardRequest, control);

    } catch (const ReaderBrokenCommunicationException& e) {
        mApduRequests.clear();
        throw ReaderCommunicationException("Reader communication error", e);

    } catch (const CardBrokenCommunicationException& e) {
        mApduRequests.clear();
        throw CardCommunicationException("Card communication error", e);

    } catch (const UnexpectedStatusWordException& e) {
        mApduRequests.clear();
        throw InvalidCardResponseException("APDU error", e);
    }

    mApduRequests.clear();

    for (const auto& apduResponse : cardResponse->getApduResponses()) {
        mApduResponses.push_back(apduResponse->getApdu());
    }

    return *this;
}

const std::vector<std::vector<uint8_t>>
CardTransactionManagerAdapter::getResponsesAsByteArrays()
{
    return mApduResponses;
}

const std::vector<std::string>
CardTransactionManagerAdapter::getResponsesAsHexStrings()
{
    std::vector<std::string> apduResponsesHex;

    for (const auto& bytes : mApduResponses) {
        apduResponsesHex.push_back(HexUtil::toHex(bytes));
    }

    return apduResponsesHex;
}

} /* namespace generic */
} /* namespace card */
} /* namespace keyple */
