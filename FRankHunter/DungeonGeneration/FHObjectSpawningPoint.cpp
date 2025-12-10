// Copyright F Rank Hunter. All Rights Reserved.


#include "DungeonGeneration/FHObjectSpawningPoint.h"
#include "FRankHunter.h"
#include "Components/ArrowComponent.h"
#include "Components/ChildActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DungeonGeneration/FHSpawningPointDescriptor.h"

void AFHObjectSpawningPoint::ShowPreviewActor()
{
	if (!SpawningPointDescriptor) return;
	if (!PreviewActor) return;

	if (previewIdx >= SpawningPointDescriptor->SpawnableActorList.Num())
	{
		previewIdx = 0;
		return;
	}
	TSubclassOf<AActor> target = SpawningPointDescriptor->SpawnableActorList[previewIdx].actor;
	PreviewActor->SetChildActorClass(target);

	++previewIdx;
	if (previewIdx >= SpawningPointDescriptor->SpawnableActorList.Num())
	{
		previewIdx = 0;
	}
}

void AFHObjectSpawningPoint::HidePreviewActor()
{
	if (!PreviewActor) return;
	PreviewActor->SetChildActorClass(nullptr);
}

AFHObjectSpawningPoint::AFHObjectSpawningPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	SetRootComponent(ArrowComponent);

	PreviewActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("PreviewActor"));
	PreviewActor->SetupAttachment(ArrowComponent);
}

void AFHObjectSpawningPoint::BeginPlay()
{
	Super::BeginPlay();

	PreviewActor->SetChildActorClass(nullptr);
}
