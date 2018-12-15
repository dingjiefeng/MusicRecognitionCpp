//#include "spdlog.h"

//namespace spd = spdlog;
//void demo()
//{
////	prepare_logdir();
//	std::string filename = "logs//simple_log";
//
//	auto console = spdlog::create<spdlog::sinks::simple_file_sink_mt>("logger", filename);
//	console->set_pattern("%v");
//
////	std::string filename = "logs/spdlog_example";
////	auto console = spd::stdout_logger_mt("console");
//	console->info("Welcome to spdlog!");
////	console->info() << "Creating file " << filename << "..";
//	
//	auto file_logger = spd::rotating_logger_mt("file_logger", filename, 1024 * 1024 * 5, 3);
//	file_logger->info("Log file message number {}", 1);
//
//	for (int i = 0; i < 100; ++i)
//	{
//		auto square = i*i;
//		//file_logger->info() << i << '*' << i << '=' << square << " (" << "0x" << std::hex << square << ")";
//	}
//
//	// Change log level to all loggers to warning and above
//	spd::set_level(spd::level::warn);
//	console->info("This should not be displayed");
//	console->warn("This should!");
//	spd::set_level(spd::level::info);
//
//	// Change format pattern to all loggers
//	spd::set_pattern(" **** %Y-%m-%d %H:%M:%S.%e %l **** %v");
//	spd::get("console")->info("This is another message with different format");
//}

//int main()
//{
//	demo();
//	system("pause");
//	return 0;
//}