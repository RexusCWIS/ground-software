#include "serialframedescriptor.h"

SerialFrameDescriptor::SerialFrameDescriptor(int frameSize,
                                             const QString &synchronisationFrame,
                                             SerialFrameDescriptor::CRC crcType) {

    m_syncFrame = synchronisationFrame;
    m_dataSize  = frameSize - m_syncFrame.size() - 2;
    m_crcType   = crcType;

    m_size = frameSize;
}

SerialFrameDescriptor::SerialFrameDescriptor() {

    m_syncFrame = "U";
    m_dataSize  = 1;
    m_size      = 2;
    m_crcType   = SerialFrameDescriptor::NO_CRC;
}

QString SerialFrameDescriptor::getSynchronisationFrame(void) const {

    return m_syncFrame;
}

int SerialFrameDescriptor::size(void) const {

    return m_size;
}

int SerialFrameDescriptor::getDataSize(void) const {

    return m_dataSize;
}

bool SerialFrameDescriptor::hasCRC(void) const {

    return (m_crcType != SerialFrameDescriptor::NO_CRC);
}
