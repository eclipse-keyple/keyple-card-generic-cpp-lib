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

#pragma once

#include <string>
#include <vector>

/* Calypsonet Terminal Card */
#include "CardSelectionResponseApi.h"
#include "SmartCardSpi.h"

/* Calypsonet Terminal Reader */
#include "SmartCard.h"

namespace keyple {
namespace card {
namespace generic {

using namespace calypsonet::terminal::card;
using namespace calypsonet::terminal::card::spi;
using namespace calypsonet::terminal::reader::selection::spi;

/**
 * (package-private)<br>
 * Implementation of a generic {@link SmartCard}.
 *
 * @since 2.0.0
 */
class GenericCardAdapter final : public SmartCard, public SmartCardSpi {
public:
    /**
     * Constructor
     *
     * <p>Gets ATR and FCI from the CardSelectionResponseApi if they exist (both are
     * optional).
     *
     * @param cardSelectionResponse The CardSelectionResponseApi from the selection process.
     */
    GenericCardAdapter(std::shared_ptr<CardSelectionResponseApi> cardSelectionResponse);

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::string& getPowerOnData() const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::vector<uint8_t> getSelectApplicationResponse() const override;

private:
    /**
     *
     */
    const std::vector<uint8_t> mSelectApplicationResponse;

    /**
     *
     */
    const std::string mPowerOnData;
};

}
}
}
