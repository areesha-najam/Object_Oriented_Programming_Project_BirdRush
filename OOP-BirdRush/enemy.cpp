#include "Enemy.hpp"

Enemy::Enemy()
{
}

void Enemy::drawObjects(SDL_Texture *texture, SDL_Renderer *renderer)
{
    assets = texture;
    gRenderer = renderer;
    SDL_RenderCopy(gRenderer, assets, &src, &mover);
}
SDL_Rect Enemy::getMover()
{
    return mover;
}
void Enemy::setAttack(bool A) {
    attack = A;
}

bool Enemy::Attack() {
    return attack;
}
