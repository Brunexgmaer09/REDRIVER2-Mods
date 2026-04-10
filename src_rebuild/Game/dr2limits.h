#ifndef DRLIMITS_H
#define DRLIMITS_H

// DRIVER 2 game engine limits
// please populate this file only with engine limits during refactoring


#ifndef PSX
#define DYNAMIC_LIGHTING
#define MAX_DLIGHTS				32
#endif

#ifndef PSX
#define MAX_PLAYERS				16			// used for replay streams mostly
#else
#define MAX_PLAYERS				8			// used for replay streams mostly
#endif

#define MAX_MODEL_SLOTS			1536		// DO NOT CHANGE. No effect in upping it - limited by cell types
#define MAX_CARS				150

#define CAR_BITMASK_WORDS		((MAX_CARS + 66) / 64)
#define CAR_COLLIDE_PLAYER_BIT	(CAR_BITMASK_WORDS * 64 - 1)

typedef unsigned long long CarBitmask[CAR_BITMASK_WORDS];

#define CARBM_SET(bm, idx)		((bm)[(idx) >> 6] |= (1ULL << ((idx) & 63)))
#define CARBM_CLR(bm, idx)		((bm)[(idx) >> 6] &= ~(1ULL << ((idx) & 63)))
#define CARBM_TST(bm, idx)		((bm)[(idx) >> 6] & (1ULL << ((idx) & 63)))

static inline void carbm_zero(unsigned long long* bm)
{
	int _i;
	for (_i = 0; _i < CAR_BITMASK_WORDS; _i++)
		bm[_i] = 0;
}
#define CARBM_ZERO(bm) carbm_zero(bm)

static inline int carbm_is_zero(const unsigned long long* bm)
{
	int _i;
	for (_i = 0; _i < CAR_BITMASK_WORDS; _i++)
		if (bm[_i]) return 0;
	return 1;
}
#define CARBM_IS_ZERO(bm) carbm_is_zero(bm)

static inline void carbm_copy(unsigned long long* dst, const unsigned long long* src)
{
	int _i;
	for (_i = 0; _i < CAR_BITMASK_WORDS; _i++)
		dst[_i] = src[_i];
}
#define CARBM_COPY(dst, src) carbm_copy(dst, src)

#define MAX_CAR_MODELS			5
#define MAX_PEDESTRIANS			28
#define MAX_SEATED_PEDS			20
#define MAX_PLACED_PEDS			15
#define MAX_EXPLOSION_OBJECTS	5
#define MAX_THROWN_BOMBS		5
#define MAX_MOTION_CAPTURE		24

// denting
#define MAX_DAMAGE_ZONE_VERTS	50
#define MAX_DAMAGE_ZONE_POLYS	70
#define MAX_DAMAGE_LEVELS		256

#ifndef PSX
#define MAX_DENTING_VERTS		256
#define MAX_DENTING_UVS			256
#define MAX_DENTING_LOD_UVS		256
#else
#define MAX_DENTING_VERTS		132
#define MAX_DENTING_UVS			255
#define MAX_DENTING_LOD_UVS		134
#endif

// Tyre track visuals
#define MAX_TYRE_PLAYERS		4
#ifndef PSX
#define MAX_TYRE_TRACK_WHEELS	4
#define MAX_TYRE_TRACK_PLAYERS	4
#else
#define MAX_TYRE_TRACK_WHEELS	2
#define MAX_TYRE_TRACK_PLAYERS	2
#endif

// Mission limits
// DO NOT EDIT, breaks compatibility!
#define MAX_MISSION_THREADS		16
#define MAX_MISSION_TARGETS		16

// replay definitions.
// DO NOT EDIT, breaks compatibility!
#define MAX_REPLAY_STREAMS		MAX_PLAYERS
#define MAX_REPLAY_CAMERAS		60
#define MAX_REPLAY_WAYPOINTS	150
#define MAX_REPLAY_PINGS		400

// debris limits
#define MAX_SMOKE				200
#define MAX_LEAVES				50
#define MAX_DEBRIS				60
#define MAX_GROUND_DEBRIS		16
#define MAX_DAMAGED_LAMPS		5
#define MAX_SMASHED_OBJECTS		8
#define MAX_LAMP_STREAKS		21
#define MAX_RAIN_DROPS			180

// driving games limit
#define MAX_SMASHED_CONES		6

// sound limits
#define MAX_SFX_CHANNELS		16		// DON'T CHANGE unless you have more than 24 channels (no PSX code)
#define MAX_LEVEL_ENVSOUNDS		32
#define MAX_SIREN_NOISES		2
#define MAX_CAR_NOISES			4


#endif // DRLIMITS_H