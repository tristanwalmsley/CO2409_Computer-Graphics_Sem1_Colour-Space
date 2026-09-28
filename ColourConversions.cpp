//
// ColourConversions.cpp
//
// Source file for colour conversion functions. The key functions are initially
// empty - you need to implement them for the lab exercise

// Find the minimum of three numbers (helper function for exercise below)
float Min( float f1, float f2, float f3 )
{
	float fMin = f1;
	if (f2 < fMin)
	{
		fMin = f2;
	}
	if (f3 < fMin)
	{
		fMin = f3;
	}
	return fMin;
}

// Find the maximum of three numbers (helper function for exercise below)
float Max( float f1, float f2, float f3 )
{
	float fMax = f1;
	if (f2 > fMax)
	{
		fMax = f2;
	}
	if (f3 > fMax)
	{
		fMax = f3;
	}
	return fMax;
}

// Convert an RGB colour to a HSL colour
// Convert an RGB colour to a HSL colour
void RGBToHSL(int R, int G, int B, int& H, int& S, int& L)
{
	// Convert RGB from 0–255 to 0-1 range
	float r = R / 255.0f;
	float g = G / 255.0f;
	float b = B / 255.0f;

	// Find min and max values
	float fMin = Min(r, g, b);
	float fMax = Max(r, g, b);

	// Lightness
	float l = (fMax + fMin) / 2.0f;

	float h = 0.0f;
	float s = 0.0f;

	// If max == min, it's a shade of grey
	if (fMax == fMin)
	{
		h = 0.0f;
		s = 0.0f;
	}
	else
	{
		float d = fMax - fMin;

		// Saturation
		if (l < 0.5f)
		{
			s = d / (fMax + fMin);
		}
		else
		{
			s = d / (2.0f - fMax - fMin);
		}

		// Hue
		if (fMax == r)
		{
			h = (g - b) / d;
		}
		else if (fMax == g)
		{
			h = 2.0f + (b - r) / d;
		}
		else
		{
			h = 4.0f + (r - g) / d;
		}

		h *= 60.0f;

		if (h < 0)
		{
			h += 360.0f;
		}
	}

	// Convert back to integer ranges
	H = (h);
	S = (s * 100);
	L = (l * 100);
}

// Convert a HSL colour to an RGB colour
void HSLToRGB(int H, int S, int L, int& R, int& G, int& B)
{
	float h = H / 360.0f;
	float s = S / 100.0f;
	float l = L / 100.0f;

	float r, g, b;

	// If saturation is 0, colour is grayscale
	if (s == 0.0f)
	{
		r = g = b = l;
	}
	else
	{
		float q;

		if (l < 0.5f)
		{
			q = l * (1 + s);
		}
		else
		{
			q = l + s - l * s;
		}

		float p = 2 * l - q;

		auto HueToRGB = [](float p, float q, float t) -> float
			{
				if (t < 0) t += 1;
				if (t > 1) t -= 1;

				if (t < 1.0f / 6.0f) return p + (q - p) * 6 * t;
				if (t < 1.0f / 2.0f) return q;
				if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6;

				return p;
			};

		r = HueToRGB(p, q, h + 1.0f / 3.0f);
		g = HueToRGB(p, q, h);
		b = HueToRGB(p, q, h - 1.0f / 3.0f);
	}

	R = (r * 255);
	G = (g * 255);
	B = (b * 255);
}
