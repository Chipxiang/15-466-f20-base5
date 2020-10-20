#include "Mode.hpp"

#include "Scene.hpp"
#include "WalkMesh.hpp"
#include "Sound.hpp"


#include <glm/glm.hpp>

#include <vector>
#include <deque>

struct PlayMode : Mode {
	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	//----- game state -----
	float time = 120.0f;
	int score = 0;
	//input tracking:
	struct Button {
		uint8_t downs = 0;
		uint8_t pressed = 0;
	} left, right, down, up;
	bool is_prev_left = false;
	bool curr_moved = false;
	bool is_delivering = false;
	glm::vec3 deliver_up_vec;
	bool is_picked_up = true;
	int color = 0;
	void switch_foot();

	glm::vec3 const spawn_position = glm::vec3(0.0f, 0.0f, 1.0f);

	void spawn_goods();

	std::list<Scene::Drawable>::iterator player_drawable;
	std::list<Scene::Drawable>::iterator goods_drawable;

	std::vector<Scene::Transform*> destinations;
	float valid_distance = 3.0f;
	//local copy of the game scene (so code can change it during gameplay):
	Scene scene;

	//player info:
	struct Player {
		WalkPoint at;
		//transform is at player's feet and will be yawed by mouse left/right motion:
		Scene::Transform *transform = nullptr;
		//camera is at player's head and will be pitched by mouse up/down motion:
		Scene::Camera *camera = nullptr;
	} player;
	Scene::Transform* pointer_transform = nullptr;
	std::shared_ptr<Sound::PlayingSample> bgm_loop;
};
