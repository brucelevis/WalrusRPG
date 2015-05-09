#ifndef INCLUDE_PIXEL_H
#define INCLUDE_PIXEL_H

#include <cstdint>

namespace WalrusRPG { namespace Graphics {

  /*
	 * Pixel structure
	 */
	class Pixel {
    union {
  		std::uint16_t value;
      public: // hack to be able to do pixel.r. Clever!
  		struct {
  			unsigned r : 5;
  			unsigned g : 6;
  			unsigned b : 5;
  		};
    };
    
    public:
		Pixel(std::uint16_t color);

		Pixel(Pixel &pix);

		Pixel(std::uint8_t red, std::uint8_t green, std::uint8_t blue);

		// Overloading (unsigned) typecast
		operator std::uint16_t() const;

		Pixel& operator=(unsigned value);

	};

}}

#endif