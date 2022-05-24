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

#include "CardRequestAdapter.h"

namespace keyple {
namespace card {
namespace generic {

CardRequestAdapter::CardRequestAdapter(
  const std::vector<std::shared_ptr<ApduRequestSpi>>& apduRequests, 
  const bool stopOnUnsuccessfulStatusWord)
: mApduRequests(apduRequests), mStopOnUnsuccessfulStatusWord(stopOnUnsuccessfulStatusWord) {}

const std::vector<std::shared_ptr<ApduRequestSpi>>& CardRequestAdapter::getApduRequests() const
{
    return mApduRequests;
}

bool CardRequestAdapter::stopOnUnsuccessfulStatusWord() const
{
    return mStopOnUnsuccessfulStatusWord;
}

}
}
}
