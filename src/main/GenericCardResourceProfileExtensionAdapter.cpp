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

#include "GenericCardResourceProfileExtensionAdapter.h"

/* Keyple Core Util */
#include "KeypleAssert.h"

namespace keyple {
namespace card {
namespace generic {

using namespace keyple::core::service::resource::spi;
using namespace keyple::core::util;
using namespace keyple::core::util::cpp;

GenericCardResourceProfileExtensionAdapter::GenericCardResourceProfileExtensionAdapter(
  std::shared_ptr<GenericCardSelection> genericCardSelection)
: mGenericCardSelection(genericCardSelection)
{
    Assert::getInstance().notNull(genericCardSelection, "genericCardSelection");
}

std::shared_ptr<SmartCard> GenericCardResourceProfileExtensionAdapter::matches(
    std::shared_ptr<CardReader> reader, 
    std::shared_ptr<CardSelectionManager> cardSelectionManager)
{

    if (!reader->isCardPresent()) {
        return nullptr;
    }

    cardSelectionManager->prepareSelection(mGenericCardSelection);
    std::shared_ptr<CardSelectionResult> cardSelectionResult = nullptr;

    try {
        cardSelectionResult = cardSelectionManager->processCardSelectionScenario(reader);
    } catch (const Exception& e) {
        mLogger->warn("An exception occurred while selecting the card: '%'\n", e.getMessage(), e);
    }

    if (cardSelectionResult != nullptr) {
        return cardSelectionResult->getActiveSmartCard();
    }

    return nullptr;
}

}
}
}
