// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOGLIKE_API UABCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//ĳ���Ϳ� ������ �Լ�
	void BindCharacter(class ALoglikeCharacter* LoglikeCharacter);
	//HP ���� ������Ʈ �Լ�
	void UpdateHPWidget();
	//�ʿ� ��������...?


protected:
	//AddToViewport �� ȣ��Ǵ� �Լ�
	virtual void NativeConstruct() override;
	

public:
	//HUD ���� ���� ������ �ؽ�Ʈ ��
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* DamageText;

	//HUD ���� ���� ��� �ؽ�Ʈ ��
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* LuckText;


private:
	//ĳ���� Ŭ���� ��ü
	UPROPERTY()
	ALoglikeCharacter* CurrentCharacter;

	//���α׷����� Ŭ���� ��ü
	UPROPERTY()
	class UProgressBar* HPProgressBar;
};
