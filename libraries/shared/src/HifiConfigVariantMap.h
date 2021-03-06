//
//  HifiConfigVariantMap.h
//  libraries/shared/src
//
//  Created by Stephen Birarda on 2014-04-08.
//  Copyright 2014 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef hifi_HifiConfigVariantMap_h
#define hifi_HifiConfigVariantMap_h

#include <QtCore/QStringList>

class HifiConfigVariantMap {
public:
    static QVariantMap mergeCLParametersWithJSONConfig(const QStringList& argumentList);
};

#endif // hifi_HifiConfigVariantMap_h
