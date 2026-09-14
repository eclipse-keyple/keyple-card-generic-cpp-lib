/******************************************************************************
 * Copyright (c) 2026 Calypso Networks Association https://calypsonet.org/    *
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

#include "keyple/card/generic/GenericCardApiFactoryAdapter.hpp"

#include <memory>

#include "keyple/card/generic/CardTransactionManagerAdapter.hpp"
#include "keyple/card/generic/GenericCardSelectionExtensionAdapter.hpp"

namespace keyple {
namespace card {
namespace generic {

std::unique_ptr<GenericCardSelectionExtension>
GenericCardApiFactoryAdapter::createGenericCardSelectionExtension()
{
    return std::unique_ptr<GenericCardSelectionExtensionAdapter>(
        new GenericCardSelectionExtensionAdapter());
}

std::unique_ptr<CardTransactionManager>
GenericCardApiFactoryAdapter::createCardTransaction(
    const std::shared_ptr<CardReader>& cardReader,
    const std::shared_ptr<SmartCard>& card)
{
    return std::unique_ptr<CardTransactionManagerAdapter>(
        new CardTransactionManagerAdapter(cardReader, card));
}

} /* namespace generic */
} /* namespace card */
} /* namespace keyple */
