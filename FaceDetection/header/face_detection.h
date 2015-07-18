/*
 * face_detection.h
 *
 *  Created on: Jul 16, 2015
 *      Author: armstrong
 */

#ifndef HEADER_FACE_DETECTION_H_
#define HEADER_FACE_DETECTION_H_

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

class Detector
{
	private:
	CascadeClassifier frontal_face_classifier;
	CascadeClassifier right_eye_classifier;
	CascadeClassifier left_eye_classifier;
	CascadeClassifier smile_classifier;
	CascadeClassifier eyes_classifier;

	public:
	vector<Rect> detect_faces(Mat image);
	vector<Rect> detect_right_eye(Mat image);
	vector<Rect> detect_left_eye(Mat image);
	vector<Rect> detect_smile(Mat image);
	vector<Rect> detect_eyes(Mat image);
	Detector(string frontal_face_cascade_path,
			 string right_eye_cascade_path,
			 string left_eye_cascade_path,
			 string smile_cascade_path,
			 string eyes_cascade_path);
};

#endif /* HEADER_FACE_DETECTION_H_ */
