#pragma once


namespace GNF::Common
{
	class ISystem
	{
		public:
			virtual ~ISystem() = default;
			virtual type_info& GetTypeInfo() = 0;

	};
}