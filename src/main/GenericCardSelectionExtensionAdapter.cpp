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

#include "keyple/card/generic/GenericCardSelectionExtensionAdapter.hpp"

#include <memory>

#include "keyple/card/generic/GenericCardAdapter.hpp"
#include "keyple/card/generic/GenericCardSelectionRequestAdapter.hpp"

namespace keyple {
namespace card {
namespace generic {

const int GenericCardSelectionExtensionAdapter::DEFAULT_SUCCESSFUL_CODE
    = 0x9000;

GenericCardSelectionExtensionAdapter::GenericCardSelectionExtensionAdapter()
: mSuccessfulSelectionStatusWords({0x9000})
{
}

std::unique_ptr<CardSelectionRequestSpi>
GenericCardSelectionExtensionAdapter::getCardSelectionRequest()
{
    return std::unique_ptr<GenericCardSelectionRequestAdapter>(
        new GenericCardSelectionRequestAdapter(
            mSuccessfulSelectionStatusWords));
}

std::shared_ptr<SmartCardSpi>
GenericCardSelectionExtensionAdapter::parse(
    const std::shared_ptr<CardSelectionResponseApi>& cardSelectionResponse)
{
    return std::make_shared<GenericCardAdapter>(cardSelectionResponse);
}

GenericCardSelectionExtension&
GenericCardSelectionExtensionAdapter::addSuccessfulStatusWord(
    const int statusWord)
{
    mSuccessfulSelectionStatusWords.push_back(statusWord);

    return *this;
}

} /* namespace generic */
} /* namespace card */
} /* namespace keyple */
