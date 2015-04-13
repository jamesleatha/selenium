// Licensed to the Software Freedom Conservancy (SFC) under one
// or more contributor license agreements. See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership. The SFC licenses this file
// to you under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef WEBDRIVER_IE_ASYNCATOMEXECUTOR_H_
#define WEBDRIVER_IE_ASYNCATOMEXECUTOR_H_

#include <vector>
#include "messages.h"

#define ASYNC_SCRIPT_EVENT_NAME L"WD_ASYNC_SCRIPT_START_EVENT"

namespace webdriver {

// Structure to be used for comunication between threads
struct AsyncScriptExecutorThreadContext {
  HWND hwnd;
  LPCTSTR script_source;
  int script_argument_count;
};

// We use a CWindowImpl (creating a hidden window) here because we
// want to synchronize access to the command handler. For that we
// use SendMessage() most of the time, and SendMessage() requires
// a window handle.
class AsyncScriptExecutor : public CWindowImpl<AsyncScriptExecutor> {
 public:
  DECLARE_WND_CLASS(L"WebDriverAsyncAtomWndClass")

  BEGIN_MSG_MAP(Session)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_CLOSE, OnClose)
    MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
    MESSAGE_HANDLER(WD_INIT, OnInit)
    MESSAGE_HANDLER(WD_ASYNC_SCRIPT_SET_DOCUMENT, OnSetDocument)
    MESSAGE_HANDLER(WD_ASYNC_SCRIPT_SET_ARGUMENT, OnSetArgument)
    MESSAGE_HANDLER(WD_ASYNC_SCRIPT_EXECUTE, OnExecuteScript)
    MESSAGE_HANDLER(WD_ASYNC_SCRIPT_IS_EXECUTION_COMPLETE, OnIsExecutionComplete)
    MESSAGE_HANDLER(WD_ASYNC_SCRIPT_DETACH_LISTENTER, OnDetachListener)
    MESSAGE_HANDLER(WD_ASYNC_SCRIPT_GET_RESULT, OnGetResult)
  END_MSG_MAP()

  LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnInit(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnSetDocument(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnSetArgument(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnExecuteScript(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnIsExecutionComplete(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnDetachListener(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnGetResult(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

  static unsigned int WINAPI ThreadProc(LPVOID lpParameter);

 private:
  CComPtr<IHTMLDocument2> script_host_;
  std::vector<CComVariant> script_arguments_;
  std::wstring script_source_code_;
  int script_argument_count_;
  int script_argument_index_;
  int status_code_;
  bool is_execution_completed_;
  bool is_listener_attached_;
};

} // namespace webdriver

#endif // WEBDRIVER_IE_ASYNCATOMEXECUTOR_H_

