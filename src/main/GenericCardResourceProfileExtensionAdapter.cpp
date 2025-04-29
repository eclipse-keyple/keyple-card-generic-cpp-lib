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

#include "keyple/card/generic/GenericCardResourceProfileExtensionAdapter.hpp"

#include "keyple/core/util/KeypleAssert.hpp"
#include "keyple/core/util/cpp/exception/Exception.hpp"
#include "keypop/reader/selection/CardSelectionManager.hpp"
#include "keypop/reader/selection/CardSelectionResult.hpp"
#include "keypop/reader/selection/spi/IsoSmartCard.hpp"

namespace keyple {
namespace card {
namespace generic {

using keyple::core::util::Assert;
using keyple::core::util::cpp::exception::Exception;
using keypop::reader::selection::CardSelectionManager;
using keypop::reader::selection::CardSelectionResult;
using keypop::reader::selection::spi::IsoSmartCard;

GenericCardResourceProfileExtensionAdapter::
    GenericCardResourceProfileExtensionAdapter(
        std::shared_ptr<IsoCardSelector> cardSelector,
        std::shared_ptr<GenericCardSelectionExtension>
            genericCardSelectionExtension)
: mGenericCardSelection(
    std::dynamic_pointer_cast<GenericCardSelectionExtensionAdapter>(
        genericCardSelectionExtension))
, mCardSelector(cardSelector)
{
    Assert::getInstance().notNull(
        genericCardSelectionExtension, "genericCardSelectionExtension");
}

std::shared_ptr<SmartCard>
GenericCardResourceProfileExtensionAdapter::matches(
    std::shared_ptr<CardReader> reader,
    std::shared_ptr<ReaderApiFactory> readerApiFactory)
{
    if (!reader->isCardPresent()) {
        return nullptr;
    }

    std::shared_ptr<CardSelectionManager> genericCardSelectionManager(
        readerApiFactory->createCardSelectionManager());
    genericCardSelectionManager->prepareSelection(
        mCardSelector, mGenericCardSelection);
    std::shared_ptr<CardSelectionResult> genericCardSelectionResult = nullptr;

    try {
        genericCardSelectionResult
            = genericCardSelectionManager->processCardSelectionScenario(reader);
    } catch (const Exception& e) {
        mLogger->error("Card selection failed: %\n", e.getMessage(), e);
    }

    if (genericCardSelectionResult != nullptr) {
        return genericCardSelectionResult->getActiveSmartCard();
    }

    return nullptr;
}

std::shared_ptr<SmartCard>
GenericCardResourceProfileExtensionAdapter::matches(
    std::shared_ptr<SmartCard> smartCard)
{
    if (std::dynamic_pointer_cast<IsoSmartCard>(smartCard) == nullptr) {
        return nullptr;
    }

    return smartCard;
}

} /* namespace generic */
} /* namespace card */
} /* namespace keyple */
