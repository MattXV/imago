import cv2

texture = cv2.imread('moon_heightmap.png')
blurred = cv2.blur(texture.copy(), (15, 15))

cv2.imshow('original', texture)
while cv2.waitKey(10) != ord('q'):
	pass

cv2.imshow('blurred', blurred)
while cv2.waitKey(10) != ord('q'):
	pass


ret = cv2.imwrite('blurred.png', blurred)
if ret:
	print('image written successfully!')