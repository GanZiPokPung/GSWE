#pragma once

#define DECLARE_SINGLETON(ClassName)\
public:								\
static ClassName* GetInstance()		\
{									\
	if(m_Instance == nullptr)		\
		m_Instance = new ClassName; \
	return m_Instance;				\
}									\
static void ReleaseInstance()		\
{									\
	if(m_Instance)					\
		delete m_Instance;			\
	m_Instance = nullptr;			\
}									\
private:							\
static ClassName* m_Instance;		\
private:							\
ClassName();

#define INIT_SINGLETON(ClassName)\
ClassName* ClassName::m_Instance = nullptr;