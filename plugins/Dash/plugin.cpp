/*
 * Copyright (C) 2013 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "plugin.h"

#include "croppedimagesizer.h"
#include "horizontaljournal.h"
#include "listviewwithpageheader.h"
#include "organicgrid.h"
#include "verticaljournal.h"

#include <QAbstractItemModel>
#include <QUrlQuery>

static QUrl oauthCleanedUrl(QUrl u)
{
    QUrlQuery q(u);
    q.removeQueryItem("oauth_nonce");
    q.removeQueryItem("oauth_timestamp");
    q.removeQueryItem("oauth_consumer_key");
    q.removeQueryItem("oauth_signature_method");
    q.removeQueryItem("oauth_version");
    q.removeQueryItem("oauth_signature");
    u.setQuery(q);
    return u;
}

class AudioComparer : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE bool compare(const QUrl &url1, const QUrl &url2)
    {
        return oauthCleanedUrl(url1) == oauthCleanedUrl(url2);
    }
};

static QObject *audio_comparer_singleton_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new AudioComparer();
}

void DashPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("Dash"));
    qmlRegisterType<QAbstractItemModel>();
    qmlRegisterType<HorizontalJournal>(uri, 0, 1, "HorizontalJournal");
    qmlRegisterType<ListViewWithPageHeader>(uri, 0, 1, "ListViewWithPageHeader");
    qmlRegisterType<OrganicGrid>(uri, 0, 1, "OrganicGrid");
    qmlRegisterType<VerticalJournal>(uri, 0, 1, "VerticalJournal");
    qmlRegisterType<CroppedImageSizer>(uri, 0, 1, "CroppedImageSizer");
    qmlRegisterSingletonType<AudioComparer>(uri, 0, 1, "AudioUrlComparer", audio_comparer_singleton_provider);
}

#include "plugin.moc"
