// Fill out your copyright notice in the Description page of Project Settings.

#include "AttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "CharacterBase.h"

UAttributeSetBase::UAttributeSetBase()
	: Health(200.f),
	MaxHealth(200.f),
	Mana(100.f),
	MaxMana(100.f),
	Strength(250.f),
	MaxStrength(250.f)
{
}

void UAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)
{
	if (Data.EvaluatedData.Attribute.GetUProperty() 
		== FindFieldChecked<UProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Health)))
	{
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.f, MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.f, MaxHealth.GetCurrentValue()));
		OnHealthChange.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());

		ACharacterBase* Character = Cast<ACharacterBase>(GetOwningActor());

		if (Character)
		{
			if (Health.GetCurrentValue() == MaxHealth.GetCurrentValue())
			{				
				Character->AddGameplayTag(Character->FullHealthTag);
			}
			else
			{
				Character->RemoveGameplayTag(Character->FullHealthTag);
			}
		}		
	}

	if (Data.EvaluatedData.Attribute.GetUProperty()
		== FindFieldChecked<UProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Mana)))
	{
		Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.f, MaxMana.GetCurrentValue()));
		Mana.SetBaseValue(FMath::Clamp(Mana.GetBaseValue(), 0.f, MaxMana.GetCurrentValue()));
		OnManaChange.Broadcast(Mana.GetCurrentValue(), MaxMana.GetCurrentValue());
	}

	if (Data.EvaluatedData.Attribute.GetUProperty()
		== FindFieldChecked<UProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Strength)))
	{
		Strength.SetCurrentValue(FMath::Clamp(Strength.GetCurrentValue(), 0.f, MaxStrength.GetCurrentValue()));
		Strength.SetBaseValue(FMath::Clamp(Strength.GetBaseValue(), 0.f, MaxStrength.GetCurrentValue()));
		OnStrengthChange.Broadcast(Strength.GetCurrentValue(), MaxStrength.GetCurrentValue());
	}
}

