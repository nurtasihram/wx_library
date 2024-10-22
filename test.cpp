#include "realtime.h"
#include "window.h"

using namespace WX;

ConsoleCtl con;

void test_thread() {
	struct BaseOf_Thread(Thread_NormalReturn) {
		inline DWORD OnStart() {
			con.Log(S("\nThread >> normal return"));
			return 1234;
		}
	} thr1;
	struct BaseOf_Thread(Thread_AssertDefaultAnswer) {
		bool bRetry = false;
		inline DWORD OnStart() {
			con.Log(S("\nThread >> answer exception with default dialog\n"));
			assertl(false);
			return 4321;
		}
	} thr2;
	struct BaseOf_Thread(Thread_AssertDuoAnswer) {
		bool bRetried = false;
		inline DWORD OnStart() {
			con.Log(S("\nThread >> answer exception\n"));
			assertl(false);
			return 4321;
		}
		inline wx_answer OnCatch(const Exception &err) {
			con.Log(S("Exception Information:"), err.toString());
			if (!bRetried) {
				bRetried = true;
				con.Log(S("\nThread >> exception retry\n"));
				wx_answer_retry;
			}
			con.Log(S("\nThread >> exception ignore\n"));
			wx_answer_ignore;
		}
	} thr3;
	struct BaseOf_Thread(Thread_AssertVoidAnswer) {
		inline DWORD OnStart() {
			con.Log(S("\nThread >> throw exception\n"));
			assertl(false);
			return 4321;
		}
		inline void OnCatch(const Exception &err) {
			con.Log(S("Exception Information:"), err.toString());
		}
		inline DWORD OnFinal() {
			return 7777;
		}
	} thr4;

	auto print_exit_code = [](auto &thr) {
		assertl(thr.Create());
		thr.WaitForSignal();
		con.Log(S("\n> ExitCode: "), thr.ExitCode(), '\n');
		system("pause");
	};

	print_exit_code(thr1);
	print_exit_code(thr2);
	print_exit_code(thr3);
	print_exit_code(thr4);
}

int main() {

	test_thread();

	return 0;

}
