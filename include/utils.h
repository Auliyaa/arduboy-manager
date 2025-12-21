#pragma once

#include <QStringList>

static constexpr const quint16 VENDOR_ID = 0x2341;
static constexpr const quint16 PRODUCT_ID1 = 0x8037;
static constexpr const quint16 PRODUCT_ID2 = 0x0037;

QString joinPath(const QStringList& elts);
QString appsPath();
QString appPath(const QString&);