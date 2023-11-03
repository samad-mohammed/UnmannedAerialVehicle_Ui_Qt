import cv2
import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QQuickWidget
from PyQt5.QtCore import QTimer

class CameraFeedApp(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Camera Feed App")
        self.setGeometry(100, 100, 800, 600)

        self.quick_widget = QQuickWidget(self)
        self.quick_widget.setSource(QUrl('qrc:/qml/CameraFeed.qml'))  # Load your QML file
        self.quick_widget.setResizeMode(QQuickWidget.SizeRootObjectToView)
        self.setCentralWidget(self.quick_widget)

        # Capture camera feed
        self.capture = cv2.VideoCapture("v4l2src ! videoconvert ! appsink name=sink", cv2.CAP_GSTREAMER)
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update_camera_feed)
        self.timer.start(1000 / 30)  # 30 FPS

    def update_camera_feed(self):
        ret, frame = self.capture.read()
        if ret:
            self.quick_widget.rootObject().setProperty("imageSource", QImage(frame, frame.shape[1], frame.shape[0], frame.strides[0], QImage.Format_RGB888))

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = CameraFeedApp()
    window.show()
    sys.exit(app.exec_())
