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

#include "GenericCardSelectionAdapter.h"

/* Keyple Card Generic */
#include "GenericCardAdapter.h"
#include "GenericCardSelectionRequestAdapter.h"

/* Keyple Core Util */
#include "ByteArrayUtil.h"
#include "IllegalArgumentException.h"
#include "KeypleAssert.h"
#include "Pattern.h"
#include "PatternSyntaxException.h"

namespace keyple {
namespace card {
namespace generic {

using namespace keyple::core::util;
using namespace keyple::core::util::cpp;
using namespace keyple::core::util::cpp::exception;

const int GenericCardSelectionAdapter::AID_MIN_LENGTH = 5;
const int GenericCardSelectionAdapter::AID_MAX_LENGTH = 16;

GenericCardSelectionAdapter::GenericCardSelectionAdapter()
: mCardSelector(std::make_shared<CardSelectorAdapter>()) {}

const std::shared_ptr<CardSelectionRequestSpi>
    GenericCardSelectionAdapter::getCardSelectionRequest()
{
        return std::make_shared<GenericCardSelectionRequestAdapter>(mCardSelector);
}

const std::shared_ptr<SmartCardSpi> GenericCardSelectionAdapter::parse(
    const std::shared_ptr<CardSelectionResponseApi> cardSelectionResponse)
{
    return std::make_shared<GenericCardAdapter>(cardSelectionResponse);
}


GenericCardSelection& GenericCardSelectionAdapter::filterByCardProtocol(
    const std::string& cardProtocol)
{
    Assert::getInstance().notEmpty(cardProtocol, "cardProtocol");

    mCardSelector->filterByCardProtocol(cardProtocol);

    return *this;
}

GenericCardSelection& GenericCardSelectionAdapter::filterByPowerOnData(
    const std::string& powerOnDataRegex)
{
    Assert::getInstance().notEmpty(powerOnDataRegex, "powerOnDataRegex");

    try {
        Pattern::compile(powerOnDataRegex);
    } catch (const PatternSyntaxException& e) {
        (void)e;
        throw IllegalArgumentException("Invalid regular expression: " + powerOnDataRegex);
    }

    mCardSelector->filterByPowerOnData(powerOnDataRegex);

    return *this;
}

GenericCardSelection& GenericCardSelectionAdapter::filterByDfName(const std::vector<uint8_t>& aid)
{
    Assert::getInstance().isInRange(static_cast<int>(aid.size()),
                                    AID_MIN_LENGTH,
                                    AID_MAX_LENGTH,
                                    "aid");

    mCardSelector->filterByDfName(aid);

    return *this;
}

GenericCardSelection& GenericCardSelectionAdapter::filterByDfName(const std::string& aid)
{
    filterByDfName(ByteArrayUtil::fromHex(aid));

    return *this;
}

GenericCardSelection& GenericCardSelectionAdapter::setFileOccurrence(
    const FileOccurrence fileOccurrence)
{
    switch (fileOccurrence) {
    case FileOccurrence::FIRST:
        mCardSelector->setFileOccurrence(CardSelectorSpi::FileOccurrence::FIRST);
        break;
    case FileOccurrence::LAST:
        mCardSelector->setFileOccurrence(CardSelectorSpi::FileOccurrence::LAST);
        break;
    case FileOccurrence::NEXT:
        mCardSelector->setFileOccurrence(CardSelectorSpi::FileOccurrence::NEXT);
        break;
    case FileOccurrence::PREVIOUS:
        mCardSelector->setFileOccurrence(CardSelectorSpi::FileOccurrence::PREVIOUS);
        break;
    }

    return *this;
}

GenericCardSelection& GenericCardSelectionAdapter::setFileControlInformation(
    const FileControlInformation fileControlInformation) {

    switch (fileControlInformation) {
    case FileControlInformation::FCI:
        mCardSelector->setFileControlInformation(CardSelectorSpi::FileControlInformation::FCI);
        break;
    case FileControlInformation::FCP:
        mCardSelector->setFileControlInformation(CardSelectorSpi::FileControlInformation::FCP);
        break;
    case FileControlInformation::FMD:
        mCardSelector->setFileControlInformation(CardSelectorSpi::FileControlInformation::FMD);
        break;
    case FileControlInformation::NO_RESPONSE:
        mCardSelector->setFileControlInformation(CardSelectorSpi::FileControlInformation::NO_RESPONSE);
        break;
    }

    return *this;
}

GenericCardSelection& GenericCardSelectionAdapter::addSuccessfulStatusWord(const int statusWord)
{
    mCardSelector->addSuccessfulStatusWord(statusWord);

    return *this;
}

}
}
}
