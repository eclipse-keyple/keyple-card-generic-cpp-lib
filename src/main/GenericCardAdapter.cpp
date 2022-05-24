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

#include "GenericCardAdapter.h"

namespace keyple {
namespace card {
namespace generic {

GenericCardAdapter::GenericCardAdapter(
  std::shared_ptr<CardSelectionResponseApi> cardSelectionResponse)
: mSelectApplicationResponse(
      cardSelectionResponse->getSelectApplicationResponse() != nullptr ?
          cardSelectionResponse->getSelectApplicationResponse()->getApdu() :
          std::vector<uint8_t>()),
          mPowerOnData(cardSelectionResponse->getPowerOnData()) {}

const std::string& GenericCardAdapter::getPowerOnData() const
{
    return mPowerOnData;
}

const std::vector<uint8_t> GenericCardAdapter::getSelectApplicationResponse() const
{
    return mSelectApplicationResponse;
}

}
}
}
