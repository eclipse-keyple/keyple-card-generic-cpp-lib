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

#include "keyple/card/generic/CardRequestAdapter.hpp"

#include <memory>
#include <vector>

#include "keyple/card/generic/ApduRequestAdapter.hpp"

namespace keyple {
namespace card {
namespace generic {

CardRequestAdapter::CardRequestAdapter(
    const std::vector<std::shared_ptr<ApduRequestSpi>>& apduRequests,
    const bool stopOnUnsuccessfulStatusWord)
: mApduRequests(apduRequests)
, mStopOnUnsuccessfulStatusWord(stopOnUnsuccessfulStatusWord)
{
}

const std::vector<std::shared_ptr<ApduRequestSpi>>&
CardRequestAdapter::getApduRequests() const
{
    return mApduRequests;
}

bool
CardRequestAdapter::stopOnUnsuccessfulStatusWord() const
{
    return mStopOnUnsuccessfulStatusWord;
}

std::ostream&
operator<<(std::ostream& os, const CardRequestAdapter& cra)
{
    os << "CARD_REQUEST_ADAPTER: {"
       << "APDU_REQUESTS = [";

    for (size_t i = 0; i < cra.mApduRequests.size(); i++) {
        if (i > 0) {
            os << ", ";
        }
        os << std::dynamic_pointer_cast<ApduRequestAdapter>(
            cra.mApduRequests[i]);
    }

    os << "], "
       << "STOP_ON_UNSUCCESSFUL_STATUS_WORD = "
       << cra.mStopOnUnsuccessfulStatusWord << "}";

    return os;
}

std::ostream&
operator<<(std::ostream& os, const std::shared_ptr<CardRequestAdapter> cra)
{
    os << *cra.get();

    return os;
}

} /* namespace generic */
} /* namespace card */
} /* namespace keyple */
