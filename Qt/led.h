#ifndef LED_H
#define LED_H

#include <QWidget>

class Led : public QWidget {
  Q_OBJECT
  Q_PROPERTY(bool power READ power WRITE setPower NOTIFY powerChanged)
  Led(const Led&) = delete;
  Led& operator=(const Led&) = delete;
 public:
  explicit Led(QWidget* parent = nullptr);
  bool power() const;
 public slots:
  void setPower(bool power);
 signals:
  void powerChanged(bool);
 protected:
  virtual void paintEvent(QPaintEvent* event) override;
 private:
  bool m_power;
};
#endif // LED_HH
