#pragma once
#include <memory>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <string>
#include "Window.h"
#include "StaticEntity.h"
#include "Vertex.h"
#include <bx/math.h>
#include <bx/debug.h>

struct BgfxCallback : public bgfx::CallbackI
{
	virtual ~BgfxCallback()
	{
	}

	virtual void fatal(const char* _filePath, uint16_t _line, bgfx::Fatal::Enum _code, const char* _str) override
	{
		BX_UNUSED(_filePath, _line);

		// Something unexpected happened, inform user and bail out.
		printf("Fatal error: 0x%08x: %s", _code, _str);

		// Must terminate, continuing will cause crash anyway.
		/*abort();*/
	}

	virtual void traceVargs(const char* _filePath, uint16_t _line, const char* _format, va_list _argList) override
	{
		printf("Trace: %s (%d): ", _filePath, _line);
		vprintf(_format, _argList);
	}

	virtual void profilerBegin(const char* /*_name*/, uint32_t /*_abgr*/, const char* /*_filePath*/, uint16_t /*_line*/) override
	{
	}

	virtual void profilerBeginLiteral(const char* /*_name*/, uint32_t /*_abgr*/, const char* /*_filePath*/, uint16_t /*_line*/) override
	{
	}

	virtual void profilerEnd() override
	{
	}

	virtual uint32_t cacheReadSize(uint64_t _id) override
	{
		return 0;
	}

	virtual bool cacheRead(uint64_t _id, void* _data, uint32_t _size) override
	{
		return false;
	}

	virtual void cacheWrite(uint64_t _id, const void* _data, uint32_t _size) override
	{
	}

	virtual void screenShot(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _data, uint32_t /*_size*/, bool _yflip) override
	{
	}

	virtual void captureBegin(uint32_t _width, uint32_t _height, uint32_t /*_pitch*/, bgfx::TextureFormat::Enum /*_format*/, bool _yflip) override
	{
	}

	virtual void captureEnd() override
	{
	}

	virtual void captureFrame(const void* _data, uint32_t /*_size*/) override
	{
	}
};

class RendererManager
{
	private:
		bgfx::VertexLayout vertex_layout_;
		bgfx::ProgramHandle shader_program_handle_;
		uint16_t view_width_;
		uint16_t view_height_;
		BgfxCallback callbacker;

	public:
		RendererManager(Window* window);
		~RendererManager();
		void PaintNextFrame(StaticEntity& static_entity, int x_modifier, int y_modifier);
		bgfx::VertexBufferHandle CreateVertexBuffer(Vertex* vertices);
		bgfx::IndexBufferHandle CreateIndexBuffer(uint16_t* indices);
		bgfx::ProgramHandle LoadShaderProgram(std::string vertex_shader_path, std::string fragment_shader_path);
};

