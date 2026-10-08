#ifndef OS_XBOX360_H
#define OS_XBOX360_H

#include "core/os/os.h"

class OS_Xbox360 : public OS {
	VideoMode current_videomode;
	MainLoop *main_loop;
	uint64_t timebase_start;

protected:
	virtual void initialize_core();
	virtual Error initialize(const VideoMode &p_desired, int p_video_driver, int p_audio_driver);
	virtual void finalize();
	virtual void finalize_core();
	virtual void set_main_loop(MainLoop *p_main_loop);
	virtual void delete_main_loop();
	virtual bool _check_internal_feature_support(const String &p_feature);

public:
	virtual String get_name() const;
	virtual void alert(const String &p_alert, const String &p_title = "ALERT!");
	virtual String get_stdin_string();
	virtual Point2 get_mouse_position() const;
	virtual int get_mouse_button_state() const;
	virtual void set_window_title(const String &p_title);
	virtual void set_video_mode(const VideoMode &p_video_mode, int p_screen = 0);
	virtual VideoMode get_video_mode(int p_screen = 0) const;
	virtual void get_fullscreen_mode_list(List<VideoMode> *p_list, int p_screen = 0) const;
	virtual int get_current_video_driver() const;
	virtual int get_video_driver_count() const;
	virtual const char *get_video_driver_name(int p_driver) const;
	virtual Error get_entropy(uint8_t *r_buffer, int p_bytes);
	virtual Size2 get_window_size() const;
	virtual bool can_draw() const;
	virtual Error execute(const String &p_path, const List<String> &p_arguments, bool p_blocking = true, ProcessID *r_child_id = nullptr, String *r_pipe = nullptr, int *r_exitcode = nullptr, bool read_stderr = false, Mutex *p_pipe_mutex = nullptr, bool p_open_console = false);
	virtual Error kill(const ProcessID &p_pid);
	virtual bool is_process_running(const ProcessID &p_pid) const;
	virtual bool has_environment(const String &p_var) const;
	virtual String get_environment(const String &p_var) const;
	virtual bool set_environment(const String &p_var, const String &p_value) const;
	virtual MainLoop *get_main_loop() const;
	virtual Date get_date(bool local = false) const;
	virtual Time get_time(bool local = false) const;
	virtual TimeZoneInfo get_time_zone_info() const;
	virtual void delay_usec(uint32_t p_usec) const;
	virtual uint64_t get_ticks_usec() const;

public:
	void run();

	OS_Xbox360();
};

#endif // OS_XBOX360_H