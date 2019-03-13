#ifndef qrow_h__
#define qrow_h__

#include <qtl/vector.h>
#include <qtl/string.h>

#include "qsql/qdatatype.h"

namespace qsql
{
	class QField;
	class QRow;
	class QTable;

	class QField
	{
		QField(const QDataType type, void* value);
	public:
		QDataType getType() const;

		template<typename T>
		T& get();
	private:
		QDataType __type;
		void* __value;
	};

	template<typename T>
	inline T& QField::get()
	{
		return *reinterpret_cast<T*>(__value);
	}

	class QRow
	{
		QRow(const qtl::vector<QField>& fields, void* data);
	public:
		QField get(const size_t column) const;
	private:
		qtl::vector<QField> __fields;
		void* __data;
	};

	class QTable
	{
	public:
	private:
		qtl::vector<QRow> __rows;
		void* __data;
	};
}

#endif // qrow_h__
