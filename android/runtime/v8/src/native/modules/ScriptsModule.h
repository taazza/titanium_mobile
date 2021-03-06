/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
#ifndef SCRIPTS_MODULE_H
#define SCRIPTS_MODULE_H

#include <v8.h>
#include "../NativeObject.h"

namespace titanium {

class ScriptsModule
{
public:
	static void Initialize(v8::Handle<v8::Object> target);
	static void Dispose();

	static v8::Handle<v8::Object> WrapContext(v8::Persistent<v8::Context> context);
};

class WrappedContext: NativeObject
{
public:
	static void Initialize(v8::Handle<v8::Object> target);
	static v8::Handle<v8::Value> New(const v8::Arguments& args);

	v8::Persistent<v8::Context> GetV8Context();
	v8::Persistent<v8::Function> GetInitCallback();
	void SetInitCallback(v8::Persistent<v8::Function> initCallback);

	static v8::Local<v8::Object> NewInstance();
	static v8::Handle<v8::Object> WrapContext(v8::Persistent<v8::Context> context);

	static v8::Persistent<v8::FunctionTemplate> constructor_template;

protected:

	WrappedContext();
	WrappedContext(v8::Persistent<v8::Context> context);
	virtual ~WrappedContext();

	v8::Persistent<v8::Context> context_;
	v8::Persistent<v8::Function> initCallback_;
};

class WrappedScript: NativeObject
{
public:
	static void Initialize(v8::Handle<v8::Object> target);

	enum EvalInputFlags
	{
		compileCode, unwrapExternal
	};
	enum EvalContextFlags
	{
		thisContext, newContext, userContext
	};
	enum EvalOutputFlags
	{
		returnResult, wrapExternal
	};

	template<EvalInputFlags input_flag, EvalContextFlags context_flag, EvalOutputFlags output_flag>
	static v8::Handle<v8::Value> EvalMachine(const v8::Arguments& args);

	static v8::Persistent<v8::FunctionTemplate> constructor_template;

	static v8::Handle<v8::Value> New(const v8::Arguments& args);
	static v8::Handle<v8::Value> CreateContext(const v8::Arguments& arg);
	static v8::Handle<v8::Value> RunInContext(const v8::Arguments& args);
	static v8::Handle<v8::Value> RunInThisContext(const v8::Arguments& args);
	static v8::Handle<v8::Value> RunInNewContext(const v8::Arguments& args);
	static v8::Handle<v8::Value> CompileRunInContext(const v8::Arguments& args);
	static v8::Handle<v8::Value> CompileRunInThisContext(const v8::Arguments& args);
	static v8::Handle<v8::Value> CompileRunInNewContext(const v8::Arguments& args);

protected:

	WrappedScript()
		: NativeObject()
	{
	}
	virtual ~WrappedScript();

	v8::Persistent<v8::Script> script_;
};

}

#endif
