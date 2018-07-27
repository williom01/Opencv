#结合opencv和tensorflow进行图像标准化处理
import tensorflow as tf
import cv2 as cv
image=cv.imread("image.jpg")
cv.imshow("image",image)
std_image=tf.image.per_image_standardization(image)
with tf.Session() as sess:
    result=sess.run(std_image)
    print(result)
    cv.imshow("result",result)
cv.waitKey(0)
