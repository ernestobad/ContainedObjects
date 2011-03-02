#pragma once


namespace COBJ
{
	template <typename ResourceType, class CloseMethod>
	class auto_resource
	{
	public:
		auto_resource(ResourceType* ptr)
			: m_ptr(ptr)
		{
		}

		auto_resource(const auto_resource& res)
			: m_ptr(ar.m_ptr)
		{
		}

		auto_resource()
			: m_ptr(NULL)
		{
		}

		~auto_resource(void)
		{
			doClose();
		}

		auto_resource<ResourceType,CloseMethod>& operator=(const auto_resource& ar)
		{
			if (m_ptr != ar.ptr)
			{
				doClose();
				m_ptr = ar.m_ptr;
			}

			return *this;
		}

		auto_resource<ResourceType,CloseMethod>& operator=(ResourceType* ptr)
		{
			if (m_ptr != ptr)
			{
				doClose();
				m_ptr = ptr;
			}

			return *this;
		}

		bool operator==(ResourceType* ptr)
		{
			return (m_ptr == ptr);
		}
		
		ResourceType& operator*() const
		{
			return *m_ptr;
		}

		ResourceType* operator->() const
		{
			return m_ptr;
		}

		ResourceType* get() const
		{
			return m_ptr;
		}

	private:
		void doClose()
		{
			if (m_ptr != NULL)
			{
				CloseMethod::close(m_ptr);
				m_ptr = NULL;
			}
		}

		ResourceType* m_ptr;
	};

	template <typename ResourceType>
	class Antlr3ResourceFree
	{
	public:
		static inline void close(ResourceType* ptr)
		{
			ptr->free(ptr);
		}
	};

	template <typename ResourceType>
	class Antlr3ResourceClose
	{
	public:
		static inline void close(ResourceType* ptr)
		{
			ptr->close(ptr);
		}
	};

	template <typename Antlr3Type>
	struct fantlr3_auto_resource
	{
		typedef auto_resource<Antlr3Type, Antlr3ResourceFree<Antlr3Type>> Type;
	};

	template <typename Antlr3Type>
	struct cantlr3_auto_resource
	{
		typedef auto_resource<Antlr3Type, Antlr3ResourceClose<Antlr3Type>> Type;
	};
}