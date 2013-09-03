//
//  Faceshift.cpp
//  interface
//
//  Created by Andrzej Kapolka on 9/3/13.
//  Copyright (c) 2013 High Fidelity, Inc. All rights reserved.
//

#include "Faceshift.h"

using namespace fs;

Faceshift::Faceshift() : _enabled(false) {
    connect(&_socket, SIGNAL(readyRead()), SLOT(readFromSocket()));
    connect(&_socket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(connectSocket()));
}

void Faceshift::setEnabled(bool enabled) {
    if (_enabled = enabled) {
        connectSocket();
    
    } else {
        _socket.disconnectFromHost();
    }
}

void Faceshift::connectSocket() {
    if (_enabled) {
        const quint16 FACESHIFT_PORT = 33433;
        _socket.connectToHost("localhost", FACESHIFT_PORT);
    }
}

void Faceshift::readFromSocket() {
    QByteArray buffer = _socket.readAll();
    _stream.received(buffer.size(), buffer.constData());
    fsMsgPtr msg;
    for (fsMsgPtr msg; msg = _stream.get_message(); ) {
        switch (msg->id()) {
            case fsMsg::MSG_OUT_TRACKING_STATE:
                const fsTrackingData& data = static_cast<fsMsgTrackingState*>(msg.get())->tracking_data();
                if (data.m_trackingSuccessful) {
                    _headRotation = glm::quat(data.m_headRotation.w, data.m_headRotation.x,
                        data.m_headRotation.y, data.m_headRotation.z);
                    _headTranslation = glm::vec3(data.m_headTranslation.x, data.m_headTranslation.y, data.m_headTranslation.z);
                }
                break;
        }
    }
}

