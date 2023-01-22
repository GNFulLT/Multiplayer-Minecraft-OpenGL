#pragma once

namespace GNF::Core
{
	class IGameThing
	{
		public:
			virtual ~IGameThing() = default;

			virtual void OnDestroyed() = 0;
			virtual void Update() = 0;
			virtual void Render() = 0;
			virtual void OnCreated() = 0;
		protected:
	};
}