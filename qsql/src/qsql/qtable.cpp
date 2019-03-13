#include "qsql/qtable.h"

namespace qsql
{
	QField::QField(const QDataType type, void* value)
		: __type(type), __value(value)
	{
	}

	QDataType QField::getType() const
	{
		return __type;
	}

	QRow::QRow(const qtl::vector<QField>& fields, void* data)
		: __fields(fields), __data(data)
	{
	}

	QField QRow::get(const size_t column) const
	{
		return __fields[column];
	}
}