#pragma once
#include "IRSegmentation.h" //Has a bunch of includes
#include "RealSense.h"
#include "Utils.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <zstd.h>


//For file management
#include <filesystem>

namespace fs = std::filesystem;

//Header put into the csv file
const std::string SCANNING_CSV_HEADER="System Time,Run Time (seconds),Depth Frame #,US Frame #," 
"CAM_T_US:,T00,T01,T02,R00,R01,R02,R10,R11,R12,R20,R21,R22,FORCE_RAW:,fr0,fr1,fr2,fr3,fr4,fr5,"
"fr6,fr7,fr8,fr9,fr10,fr11,FORCE_XYZ:,fx,fy,fz,IMU:,temp,g0,g1,g2,a0,a1,a2\n";

class Datalogger
{
public:
	//Inits the path, csv filename (scanning_datetime.csv), and csv header
	Datalogger(std::string root_path, std::string participant_directory,
		Eigen::MatrixXd& calib_mat, Eigen::Vector3d& zeroing_offset,std::string& left_camera_intrinsics, std::string& right_camera_intrinsics, double& depth_scale, int depth_width, int depth_height, double depth_fps, int us_width, int us_height, double us_fps);
	~Datalogger();

	void close();

	//Writes the data to the scan_datetime.csv
	void writeCSVRow(float &run_seconds,int &depth_frame_num,int &us_frame_num, 
		Eigen::Matrix4d& cam_T_us, std::string& raw_force_string,
		std::string& force_string_xyz, std::string& temp_imu_string);

	void writeDepthFrame(const cv::Mat& frame);
	void writeIRFrames(const cv::Mat& irLeft,const cv::Mat& irRight);
	void writeColourFrame(const cv::Mat& colourFrame);
	//void writeUSFrame(const cv::Mat& frame);

	

private:
	//Class Vars
	std::ofstream _csv_file;
	std::string _data_path,_csv_filename;
	std::string _depth_file, _us_file,_irLeft_file,_irRight_file,_rgb_file;
	FILE* _depth_pipeout;
	FILE* _us_pipeout;

	//OpenCV Video Writing Vars
	cv::VideoWriter _us_videowriter, _depth_videowriter,_irLeft_videowriter,_irRight_videowriter,_bgr_videowriter;


	void initFfmpegipe(FILE*& pipeout, std::string& file_name, std::string px_fmt);




	//FILE* _depth_pipein;
	//FILE* _depth_zstd_file;
	//FILE* _us_zstd_file;
	//ZSTD_CCtx* _depth_zstd_ctx;
	//ZSTD_CCtx* _us_zstd_ctx;
	//std::vector<char> _depth_compressed_buffer;
	

};

