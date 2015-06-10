#include "Outlet.h"

Outlet::Outlet() {
  this->status.isExist = true;
  this->status.isOn = false;
}

Outlet::Outlet(bool isExist, bool status) {
  this->status.isExist = isExist;
  this->status.isOn = status;
}

Outlet::Outlet(OutletStatus status) {
  this->status = status;
}

void Outlet::setStatus(OutletStatus status) {
  this->status = status;
}

OutletStatus Outlet::getStatus() {
  return this->status;
}
