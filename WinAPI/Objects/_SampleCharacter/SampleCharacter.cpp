#include "Framework.h"

SampleCharacter::SampleCharacter()
{
    texture = Texture::Add(L"Textures/_SampleCharacter/_SampleCharacter.bmp", 7, 10);
    imageRect = new ImageRect(texture);
    size = { 96, 96 };
    imageOffset = { 0, 0 };

    CreateAnimations();
    animations[curAction]->Play();
}

SampleCharacter::~SampleCharacter()
{
    delete imageRect;

    for (pair<ActionType, Animation*> animation : animations)
        delete animation.second;
}

void SampleCharacter::Update()
{
    Jump();
    GetHit();
    Die();

    WalkAndRun();

    Attack();
    Attack_Run();

    Attack_GetCombo();
    Attack_InputDelay();

    AutoAnimation();

    imageRect->pos = pos + imageOffset;
    animations[curAction]->Update();
}

void SampleCharacter::Render(HDC hdc)
{
    Rect::LineRender(hdc);

    imageRect->Render(hdc, isLeft, (int)alphaValue, animations[curAction]->GetFrame());
}

void SampleCharacter::Jump()
{
    if (jumpCount < 2 && (KEY_DOWN(VK_SPACE)||KEY_DOWN(VK_UP)) &&
        StageManager::Get()->IsPlay() && !isAttacking)
    {
        yVelocity = JUMP_POWER;
        jumpCount++;

        SetAction(JUMP);
    }

    yVelocity -= GRAVITY * DELTA;
    pos.y -= yVelocity * DELTA;

    Vector2 bottomPos = pos;
    bottomPos.y = Bottom() - BOTTOM_CHECK;
    float groundHeight = StageManager::Get()->GetGroundHeight(bottomPos);

    if (Bottom() > groundHeight)
    {
        if (yVelocity < 0)
        {
            yVelocity = 0.0f;
            jumpCount = 0;
            pos.y = groundHeight - Half().y;
        }
    }
}

void SampleCharacter::Attack()
{
    if (!StageManager::Get()->IsPlay()) return;
    
    if (curAction == RUN) return;
    if (attackInputDelay != 0) return;

    if (KEY_DOWN(VK_LBUTTON))
    {
        switch (attackCount)
        {
        case 0:
            SetAction(ATTACK_1);
            attackCount++;
            attackInputDelay = ATTACK_DELAY;
            isAttacking = true;
            break;

        case 1:
            SetAction(ATTACK_2);
            attackCount++;
            attackInputDelay = ATTACK_DELAY;
            isAttacking = true;
            break;

        case 2:
            SetAction(ATTACK_3);
            attackCount++;
            attackInputDelay = ATTACK_DELAY;
            isAttacking = true;
            break;
        }
    }
}

void SampleCharacter::Attack_Run()
{
    if (!StageManager::Get()->IsPlay()) return;

    if (curAction != RUN) return;
    if (attackInputDelay != 0) return;

    if (KEY_DOWN(VK_LBUTTON))
    {
        SetAction(RUN_ATTACK);
        attackInputDelay = ATTACK_DELAY;
        isAttacking = true;
    }
}

void SampleCharacter::Attack_GetCombo()
{
    if (attackComboCurrentTime < 0)
    {
        attackComboCurrentTime = 0;
        attackCount = 0;
    }

    if (attackComboCurrentTime == 0) return;
    else attackComboCurrentTime -= DELTA;
}

void SampleCharacter::Attack_InputDelay()
{
    if (attackInputDelay < 0)
    {
        attackInputDelay = 0;
    }

    if (attackInputDelay == 0) return;
    else attackInputDelay -= DELTA;
}

void SampleCharacter::WalkAndRun()
{
    if (!StageManager::Get()->IsPlay()) return;


    if (KEY_DOWN(VK_SHIFT))
    {
        if (!isHighProfile) isHighProfile = true;
    }
    
    if (KEY_UP(VK_SHIFT))
    {
        if (isHighProfile) isHighProfile = false;
    }

    if (KEY_PRESS(VK_LEFT))
    {
        if (!isLeft) isLeft = true;

        if (isHighProfile)
        {
            if (OnGround() && curAction != RUN && !isAttacking) SetAction(RUN);
            pos.x -= WALK_SPEED * RUN_MULT * DELTA; //강제 float 계산 유도
        }
        else
        {
            if (OnGround() && curAction != WALK && !isAttacking) SetAction(WALK);
            pos.x -= WALK_SPEED * DELTA;
        }
    }

    if (KEY_UP(VK_LEFT))
    {
        SetAction(IDLE);
    }

    if (KEY_PRESS(VK_RIGHT))
    {
        if (isLeft) isLeft = false;

        if (isHighProfile)
        {
            if (OnGround() && curAction != RUN && !isAttacking) SetAction(RUN);
            pos.x += WALK_SPEED * RUN_MULT * DELTA; //강제 float 계산 유도
        }
        else
        {
            if (OnGround() && curAction != WALK && !isAttacking) SetAction(WALK);
            pos.x += WALK_SPEED * DELTA;
        }
    }

    if (KEY_UP(VK_RIGHT))
    {
        SetAction(IDLE);
    }
}

bool SampleCharacter::OnGround()
{
    return (curAction != JUMP) && (curAction != JUMP_DOWN);
}

void SampleCharacter::AutoAnimation()
{
    if (curAction == HURT || isAttacking) return;
    if (yVelocity > 0.0f) return;

    if (yVelocity < 0.0f)
    {
        SetAction(JUMP_DOWN);
    }
    else
    {
        yVelocity = 0;
        if (curAction == JUMP || curAction == JUMP_DOWN) SetAction(IDLE);
    }
}

void SampleCharacter::GetHit()
{
    if (isGhost)
    {
        ghostTime += DELTA;

        if (isIncreaseAlpha)
        {
            alphaValue += ALPHA_SPEED * DELTA;
            if (alphaValue > 255.0f)
                isIncreaseAlpha = false;
        }
        else
        {
            alphaValue -= ALPHA_SPEED * DELTA;
            if (alphaValue < 0.0f)
                isIncreaseAlpha = true;
        }


        if (ghostTime >= GHOST_TIME)
        {
            isGhost = false;
            alphaValue = 255.0f;
        }
        return;
    }

    if (!StageManager::Get()->CollisionObstacle(this))
        return;

    SetAction(HURT);

    StageManager::Get()->Stop();

    isGhost = true;
    ghostTime = 0.0f;
    alphaValue = 255.0f;
    isIncreaseAlpha = false;
}

void SampleCharacter::Die()
{
    //기본 : 죽지 않으면 이 코드는 실행되지 않습니다.
    if (curAction != DEAD) return;

    //죽었을 때 실행될 코드가 추가로 발생하면 여기에 작성

    SetAction(DEAD);

    StageManager::Get()->Stop();
}

void SampleCharacter::EndGetHit()
{
    SetAction(IDLE);
    StageManager::Get()->Play();
}

void SampleCharacter::EndAttack()
{
    SetAction(IDLE);
    attackComboCurrentTime = ATTACK_COMBO;
    isAttacking = false;
}

void SampleCharacter::SetAction(ActionType type)
{
    if (curAction == type) return;

    curAction = type;
    animations[type]->Play();
}

void SampleCharacter::CreateAnimations()
{
    animations[IDLE] = new Animation(texture->GetFrame());
    animations[IDLE]->SetPart(35, 39, true);

    animations[RUN] = new Animation(texture->GetFrame());
    animations[RUN]->SetPart(49, 54, true);

    animations[WALK] = new Animation(texture->GetFrame());
    animations[WALK]->SetPart(63, 69, true);

    animations[JUMP] = new Animation(texture->GetFrame());
    animations[JUMP]->SetPart(42, 45);

    animations[JUMP_DOWN] = new Animation(texture->GetFrame());
    animations[JUMP_DOWN]->SetPart(45, 46);

    animations[HURT] = new Animation(texture->GetFrame());
    animations[HURT]->SetPart(28, 29);
    animations[HURT]->SetEndEvent(bind(&SampleCharacter::EndGetHit, this));

    animations[DEAD] = new Animation(texture->GetFrame());
    animations[DEAD]->SetPart(21, 24);

    animations[ATTACK_1] = new Animation(texture->GetFrame());
    animations[ATTACK_1]->SetPart(0, 3);
    animations[ATTACK_1]->SetEndEvent(bind(&SampleCharacter::EndAttack, this));

    animations[ATTACK_2] = new Animation(texture->GetFrame());
    animations[ATTACK_2]->SetPart(7, 11);
    animations[ATTACK_2]->SetEndEvent(bind(&SampleCharacter::EndAttack, this));

    animations[ATTACK_3] = new Animation(texture->GetFrame());
    animations[ATTACK_3]->SetPart(14, 15);
    animations[ATTACK_3]->SetEndEvent(bind(&SampleCharacter::EndAttack, this));

    animations[RUN_ATTACK] = new Animation(texture->GetFrame());
    animations[RUN_ATTACK]->SetPart(56, 60);
    animations[RUN_ATTACK]->SetEndEvent(bind(&SampleCharacter::EndAttack, this));
}
