#pragma once
#include "Brick.h"


namespace RubiksCube
{
	namespace Elements {
		class Edge : public Brick {
		public:
			Edge();
			Edge(orientation_type up, orientation_type front);
			Color_t get_color(orientation_type which);
			void rotate(orientation_type color, rotate_direction_t direction);

		private:
			Tile tile_[2];
		};
	}
}