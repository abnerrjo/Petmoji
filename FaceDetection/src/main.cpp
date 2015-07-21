#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "face_detection.h"
#include "histogram_equalization.h"
#include "smoothing.h"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

#define SMOOTHING_KERNEL_WIDTH 11
#define SMOOTHING_KERNEL_HEIGHT 11
#define SMOOTHING_TYPE NORMALIZED
#define FACE_DETECTION_SCALE_FACTOR 1.1
#define FACE_DETECTION_MIN_NEIGHBORS 2
#define FACE_DETECTION_MIN_SIZE_X 30
#define FACE_DETECTION_MIN_SIZE_Y 30

void check_arguments(int argc, char** argv)
{
	if (argc != 3)
	{
		puts("Numero incorreto de argumentos");
		exit(-1);
	}
}

vector<Mat> pre_process_faces(vector<Mat> faces, int smoothing_type, int kernel_width, int kernel_height)
{
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		Mat equalized_image = equalize_histogram(faces[i]);
		faces[i] = smoothing(faces[i], smoothing_type, kernel_width, kernel_height);
	}

	return faces;
}

void export_faces(vector<Mat> faces, char* original_face_image_filename)
{
	if (faces.size() > 1)
	{
		printf("WARNING: Achou %ld faces!\n", faces.size());
	}

	imwrite(original_face_image_filename, faces[0]);

	for (unsigned int i = 1; i < faces.size(); i++) {
		char extra_face[15];
		sprintf(extra_face, "_%d.jpg", i);
		imwrite(extra_face, faces[i]);
	}
}

int main(int argc, char** argv)
{
	check_arguments(argc, argv);
	Mat image = imread(argv[1], CV_LOAD_IMAGE_COLOR);

	Detector detector("conf/haarcascade_frontalface_alt2.xml",
				"conf/haarcascade_righteye_2splits.xml",
				"conf/haarcascade_lefteye_2splits.xml",
				"conf/haarcascade_smile.xml",
				"conf/haarcascade_eye.xml");

	vector<Mat> faces = detector.get_faces(image, FACE_DETECTION_SCALE_FACTOR, FACE_DETECTION_MIN_NEIGHBORS, FACE_DETECTION_MIN_SIZE_X, FACE_DETECTION_MIN_SIZE_Y);
	vector<Mat> processed_faces = pre_process_faces(faces, NORMALIZED, SMOOTHING_KERNEL_WIDTH, SMOOTHING_KERNEL_HEIGHT);
	export_faces(processed_faces, argv[2]);
}
