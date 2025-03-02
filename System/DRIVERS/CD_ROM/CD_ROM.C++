enum CD_ROM_STATUS {
CD_TRAY_OPENED,
CD_NO_DISC,
CD_TRAY_CLOSED,
CD_ERROR,
CD_OK = 0,
CD_CORRUPTED
}
static CD_ROM_STATUS getstatus(int disk_index) {
// My logics to read disk status
}
