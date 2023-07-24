$COPYRIGHT_LINE$


$MY_HEADER_INCLUDE_DIRECTIVE$


// Sets default values
$PREFIX$$UNPREFIXED_CLASS_NAME$::$PREFIX$$UNPREFIXED_CLASS_NAME$()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void $PREFIX$$UNPREFIXED_CLASS_NAME$::BeginPlay()
{
	Super::BeginPlay();
	$END$
}

// Called every frame
void $PREFIX$$UNPREFIXED_CLASS_NAME$::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

