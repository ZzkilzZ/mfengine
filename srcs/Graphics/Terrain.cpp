#include "Terrain.hpp"

namespace mf
{

Terrain::Terrain(int width, int length)
{
	try
	{
		mVertices = std::shared_ptr<float>( new float[width * length * 3]);
		mIndices = std::shared_ptr<unsigned int>(new unsigned int[(width - 1) * 2 * (length - 1) * 3]);
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	mVerticeSize = sizeof(float) * width * length * 3;
	mIndiceSize = sizeof(unsigned int) * (width - 1) * 2 * (length - 1) * 3;
	mWidth = width;
	mLength = length;
	InitTerrain();
	initMesh();
}

Terrain::~Terrain()
{
}

void		Terrain::InitTerrain()
{
	int i = 0, j = 0;

	while (i < mLength * mWidth * 3)
	{
		mVertices.get()[i] = ((i / 3) % (mWidth)) - (mWidth / 2);
		mVertices.get()[i + 2] = ((i / 3) / mWidth) - (mLength / 2);
		mVertices.get()[i + 1] = 0.0f;
		i += 3;
	}
	i = 0;
	j = 0;
	while (i < (mWidth - 1) * 2 * (mLength - 1) * 3)
	{
		mIndices.get()[i] = j;
		mIndices.get()[i + 1] = j + mWidth;
		mIndices.get()[i + 2] = j + 1 + mWidth;
		mIndices.get()[i + 3] = j;
		mIndices.get()[i + 4] = j + 1 + mWidth;
		mIndices.get()[i + 5] = j + 1;
		i += 6;
		j += 1;
		if (!((i / 6) % (mWidth - 1)))
			j++;
	}
}

void		Terrain::Randomize(int seed, float lower, float higher)
{
	int i = 0;
	srand(seed);
	while (i < mLength * mWidth * 3)
	{
		mVertices.get()[i + 1] = (float)(rand() % (int)(higher - lower)) / 100.0f + (lower / 100.0f);
		i += 3;
	}
	initMesh();
}

void		Terrain::GenHeightMap(int seed)
{
	if (!mVertices || !mIndices)
	{
		throw std::exception();
		return ;
	}
	noise::module::Perlin				perlin;
	noise::utils::NoiseMap				map;
	noise::utils::NoiseMapBuilderPlane	plane;
	int i = 0;

	perlin.SetSeed(seed);
	plane.SetSourceModule(perlin);
	plane.SetDestNoiseMap(map);
	plane.SetDestSize(mWidth, mLength);
	plane.SetBounds(-2.0, 13.0, -1.0, 12.0);
	plane.Build();
	while (i < mLength * mWidth * 3)
	{
		mVertices.get()[i + 1] = map.GetValue(mVertices.get()[i] + (mWidth / 2), mVertices.get()[i + 2] + (mLength / 2)) * 80;
		i += 3;
	}
	initMesh();
}

float		Terrain::GetHeightAt(int x, int z)
{
	
	x += (mWidth / 2) * 30;
	z += (mLength / 2) * 30;
	x /= 30.0;
	z /= 30.0;
	x = std::clamp(x, 0, mWidth - 1);
	z = std::clamp(z, 0, mLength - 1);
	return mVertices.get()[((z * mWidth * 3) + (x * 3) ) + 1];
}

} // namespace mf
