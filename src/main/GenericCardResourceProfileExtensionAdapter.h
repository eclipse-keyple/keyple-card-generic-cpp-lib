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

/* Keyple Core Service Resource */
#include "CardResourceProfileExtension.h"
#include "GenericCardSelection.h"

/* Keyple Core Util */
#include "LoggerFactory.h"

namespace keyple {
namespace card {
namespace generic {

using namespace keyple::core::service::resource::spi;
using namespace keyple::core::util::cpp;

/**
 * (package-private)<br>
 * Implementation of CardResourceProfileExtension dedicated to card identification.
 *
 * @since 2.0.0
 */
class GenericCardResourceProfileExtensionAdapter final : public CardResourceProfileExtension {
public:
    /**
     * (package-private)<br>
     *
     * @param genericCardSelection The GenericCardSelection.
     * @since 2.0.0
     */
    GenericCardResourceProfileExtensionAdapter(
        std::shared_ptr<GenericCardSelection> genericCardSelection);

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    std::shared_ptr<SmartCard> matches(std::shared_ptr<CardReader> reader, 
                                       std::shared_ptr<CardSelectionManager> cardSelectionManager)
        override;

private:
    /**
     * 
     */
    const std::unique_ptr<Logger> mLogger =
        LoggerFactory::getLogger(typeid(GenericCardResourceProfileExtensionAdapter));
    
    /**
     * 
     */
    std::shared_ptr<GenericCardSelection> mGenericCardSelection;
};

}
}
}
