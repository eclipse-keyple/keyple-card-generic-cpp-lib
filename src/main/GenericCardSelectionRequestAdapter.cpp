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

#include "keyple/card/generic/GenericCardSelectionRequestAdapter.hpp"

#include "keyple/core/util/cpp/KeypleStd.hpp"

namespace keyple {
namespace card {
namespace generic {

GenericCardSelectionRequestAdapter::GenericCardSelectionRequestAdapter(
    const std::vector<int>& successfulSelectionStatusWords)
: mSuccessfulSelectionStatusWords(successfulSelectionStatusWords)
{
}

const std::vector<int>&
GenericCardSelectionRequestAdapter::getSuccessfulSelectionStatusWords() const
{
    return mSuccessfulSelectionStatusWords;
}

const std::shared_ptr<CardRequestSpi>
GenericCardSelectionRequestAdapter::getCardRequest() const
{
    /* No additional command following the card selection in this extension. */
    return nullptr;
}

std::ostream&
operator<<(std::ostream& os, const GenericCardSelectionRequestAdapter& gcsra)
{
    os << "CARD_SELECTION_REQUEST: {"
       << "SUCCESSFUL_STATUS_WORD: " << gcsra.mSuccessfulSelectionStatusWords
       << "}";

    return os;
}

std::ostream&
operator<<(
    std::ostream& os,
    const std::shared_ptr<GenericCardSelectionRequestAdapter> gcsra)
{
    os << *gcsra.get();

    return os;
}

} /* namespace generic */
} /* namespace card */
} /* namespace keyple */
