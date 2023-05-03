// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "LoglikeCharacter.generated.h"


//HP üũ�� ��������Ʈ
//DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
//HP ��ȭ üũ�� ��������Ʈ
//DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);

UCLASS(config = Game, meta = (BlueprintSpawnableComponent))
class ALoglikeCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;


public:
	ALoglikeCharacter();

	/*UPROPERTY(VisibleAnywhere, Category = "Weapon")
	USkeletalMeshComponent* Weapon;*/

	//virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;


protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();


public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	//���� �ִ� ���� �Լ�
	void Attack();
	//���� �ִ� ���� �Լ�
	void Dodge();
	//�и� �ִ� ���� �Լ�
	void Parrying();
	//�޴� ������ ó�� �Լ�
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	//HUD������ HP Bar ������ ����ϴ� �Լ�
	float GetHPRatio();

	//�� HP ��������Ʈ(��������Ʈ�� ���ε��� �Լ����� ���ÿ� ���� ������)
	//FOnHPIsZeroDelegate OnHPIsZero;
	//FOnHPChangedDelegate OnHPChanged;

	//�������Ʈ���� ���� ü���� ������ �� ����� �Լ�
	UFUNCTION(BlueprintPure, Category = "Stat")
	float GetHealth();
	//�������Ʈ���� ĳ���� ���ݷ��� ������ �� ����� �Լ�
	UFUNCTION(BlueprintPure, Category = "Stat")
	float GetCharacterDamage();
	//�������Ʈ���� ĳ���� ����� ������ �� ����� �Լ�
	UFUNCTION(BlueprintPure, Category = "Stat")
	float GetCharacterLuck();
	//�������Ʈ���� ĳ���� ����� ������ �� ����� �Լ�
	UFUNCTION(BlueprintPure, Category = "Stat")
	int GetCharacterToken();


private:
	//���� ��Ÿ�� �� üũ �Լ�
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	//�޺� ���� ���� ���� üũ �Լ�
	void AttackStartComboState();
	//�޺� ���� �� ���� üũ �Լ�
	void AttackEndComboState();
	//���� �ݸ����� �Ѽ� �����ߴ��� üũ�ϴ� �Լ�
	void AttackCheck();

	//���� ��Ÿ�� �� üũ �Լ�
	UFUNCTION()
	void OnDodgeMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	//�и� ��Ÿ�� �� üũ �Լ�
	UFUNCTION()
	void OnParryingMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	
	//������ ������ �Լ�
	void Delay1();
	//�и��� ������ �Լ�
	void Delay2();


public:
	//ĳ���� ������ ����
	float CharacterDamage;
	//ĳ���� ��� ����
	float CharacterLuck;
	//ĳ���� ��� ����
	int CharacterToken;
	//ĳ���� ���� üũ(ü�� 0 üũ)
	bool IsDead;

	//HUD Ŭ���� ��ü
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UUserWidget> HUDWidgetClass;
	//���� Ŭ���� ��ü
	UPROPERTY(EditAnywhere, Category = "Widget")
	class UABCharacterWidget* CurrentWidget;


private:
	//�ִ� Ŭ���� ��ü
	UPROPERTY()
	class UABAnimInstance* ABAnim;
	//���� Ÿ�̸� �ڵ鷯
	UPROPERTY()
	FTimerHandle Dodge_Timer;
	//�и� Ÿ�̸� �ڵ鷯
	UPROPERTY()
	FTimerHandle Parrying_Timer;

	//���� üũ
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	bool IsAttacking;
	//�޺� ���� ���� üũ
	UPROPERTY(VisibleInstanceOnly, BluePrintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	bool CanNextCombo;
	//�޺� �����ϵ��� �Է��� �������� üũ(Ŭ���� �������� �������� üũ)
	UPROPERTY(VisibleInstanceOnly, BluePrintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	bool IsComboInputOn;
	//���� �޺� ��
	UPROPERTY(VisibleInstanceOnly, BluePrintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;
	//�ִ� �޺� ��
	UPROPERTY(VisibleInstanceOnly, BluePrintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	int32 MaxCombo;
	
	//���� üũ
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Dodge", Meta = (AllowPrivateAccess = true))
	bool IsDodge = false;
	//���� ���ǵ�
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Dodge", Meta = (AllowPrivateAccess = true))
	float DodgeSpeed = 500.0f;
	//���� ������ ���� üũ
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Dodge", Meta = (AllowPrivateAccess = true))
	bool DodgeDelay = false;
	
	//�и� ���� ���� üũ
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Parrying", Meta = (AllowPrivateAccess = true))
	bool IsParrying = false;
	//�и� ������ ���� üũ
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Parrying", Meta = (AllowPrivateAccess = true))
	bool ParryingDelay = false;
	
	//ĳ���� ���� �ݸ��� ����(�յ�)
	UPROPERTY(VisibleInstanceOnly, BluePrintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	float AttackRange;
	//ĳ���� ���� �ݸ��� ����(�翷)
	UPROPERTY(VisibleInstanceOnly, BluePrintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	float AttackRadius;
	
	//�¾Ҵ��� ���� üũ
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Hit", Meta = (AllowPrivateAccess = true))
	bool IsHit = false;
	//�ִ� ü��
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "State", Meta = (AllowPrivateAccess = true))
	float MaxHealth;
	//���� ü��
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "State", Meta = (AllowPrivateAccess = true))
	float CurrentHealth;
	//�¾��� �� ��ƼŬ ȿ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HitParticle", meta = (AllowPrivateAccess = true))
	UParticleSystem* HitImpactP;
};

