/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef PURCHASEHANDLER_H
#define PURCHASEHANDLER_H

#include "productshandler.h"

#include <QObject>

class PurchaseHandler : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY_MOVE(PurchaseHandler)

 public:
  static PurchaseHandler* createInstance();
  static PurchaseHandler* instance();

  // Returns the latest SKU the started to Subcribe.
  // Is empty if the user already had a subscription or never started the
  // subscription flow.
  const QString& currentSKU() const { return m_currentSKU; }

  Q_INVOKABLE void subscribe(const QString& productIdentifier);
  Q_INVOKABLE void restore();

  void startSubscription(const QString& productIdentifier);
  void startRestoreSubscription();

  // The nativeRegisterProducts method is currently here (not in
  // productshandler) for simplicity of the native implementation.
  virtual void nativeRegisterProducts() = 0;

 signals:
  void subscriptionStarted(const QString& productIdentifier);
  void restoreSubscriptionStarted();
  void subscriptionFailed();
  void subscriptionCanceled();
  void subscriptionCompleted();
  void alreadySubscribed();
  void billingNotAvailable();
  void subscriptionNotValidated();

 public slots:
  void stopSubscription();

 protected:
  PurchaseHandler(QObject* parent);
  ~PurchaseHandler();

  virtual void nativeStartSubscription(ProductsHandler::Product* product) = 0;
  virtual void nativeRestoreSubscription() = 0;

  enum State {
    eActive,
    eInactive,
  } m_subscriptionState = eInactive;

  QString m_currentSKU;
};

#endif  // PURCHASEHANDLER_H