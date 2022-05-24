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

#include "GenericCardSelectionRequestAdapter.h"

namespace keyple {
namespace card {
namespace generic {

GenericCardSelectionRequestAdapter::GenericCardSelectionRequestAdapter(
   std::shared_ptr<CardSelectorSpi> cardSelector)
: mCardSelector(cardSelector) {}

const std::shared_ptr<CardSelectorSpi> GenericCardSelectionRequestAdapter::getCardSelector() const
{
    return mCardSelector;
}

const std::shared_ptr<CardRequestSpi> GenericCardSelectionRequestAdapter::getCardRequest() const
{
    return nullptr;
}

}
}
}
