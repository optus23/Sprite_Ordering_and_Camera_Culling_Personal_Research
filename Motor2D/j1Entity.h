#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "p2Point.h"
#include "Animation.h"
#include "SDL/include/SDL_timer.h"
#include <string>
#include "j1Module.h"
#include "j1Collision.h"
#include "SDL_image/include/SDL_image.h"


struct SDL_Texture;
struct Collider;

struct TileSetEntity {

	SDL_Rect GetTileRect(int id) const;

	std::string name;
	uint tilewidth = 0;
	uint tileheight = 0;
	uint spacing = 0;
	uint margin = 0;
	uint tilecount = 0;
	uint columns = 0;
	std::string imagePath;
	SDL_Texture* texture = nullptr;
	uint width = 0;
	uint height = 0;
};

enum class EntityState {
	IDLE = 0,
	WALKING,

	UNKNOWN
};

struct EntityAnim {
	uint id = 0;
	uint num_frames = 0;
	SDL_Rect* frames = nullptr;
	EntityState animType;

	uint FrameCount(pugi::xml_node&);
};

struct EntityInfo {
	TileSetEntity tileset;
	EntityAnim* animations = nullptr;
	uint num_animations = 0;
};

struct COLLIDER_INFO {
	Collider* collider = nullptr;
	iPoint offset;
	int width = 0;
	int height = 0;
	COLLIDER_TYPE type;
};

class j1Entity
{
public:

	enum class Types
	{
		PLAYER,
		STATIC,

		UNKNOWN
	};

public:

	j1Entity(Types type, int x, int y, std::string name);
	virtual ~j1Entity();

	const Collider* GetCollider() const;

	bool LoadEntityData(const char*);
	virtual void LoadProperties(pugi::xml_node&);
	virtual void LoadCollider(pugi::xml_node&);
	virtual void IdAnimToEnum();
	virtual void PushBack() {};
	virtual void AddColliders(j1Entity* c = nullptr);

	virtual bool Start() { return true; }
	virtual bool Update(float dt);
	virtual void Move(float dt) {}
	virtual void Draw();
	virtual void CreatePath() {}
	virtual void OnCollision(Collider* collider1, Collider * collider2, float dt) {}
	virtual bool CleanUp();
	
public:

	std::string name;

	fPoint position;
	iPoint pivot;

	iPoint size;

	Types type;

	Animation anim_idle;

	COLLIDER_INFO collider;

	EntityInfo data;

	std::string folder = "entities/";

	SDL_RendererFlip flip = (SDL_RendererFlip)SDL_FLIP_NONE;

	pugi::xml_document	entity_file;
	
	Animation* current_animation = nullptr;
	float animationSpeed;
};
#endif // __ENTITY_H__