// Fill out your copyright notice in the Description page of Project Settings.


#include "BonfireManager.h"

TArray<FBonfireData> BonfireManager::BonfireDataArray = {
    { "Stage1-1", "������ ��¥���� ��Ʈ", "�ν����� ���� ��", false, nullptr },
    { "Stage1-2", "���� ���� ž", "�ν����� ���� ��", true, nullptr }
};

// ȭ����� Ȱ��ȭ ���·� ����
void BonfireManager::ActivateBonfire(FName BonfireID)
{
    for (auto& Bonfire : BonfireDataArray)  // ��� ȭ����� ��ȸ
    {
        if (Bonfire.BonfireID == BonfireID)  // ID�� ��ġ�ϸ�
        {
            Bonfire.bActivated = true;  // Ȱ��ȭ
            break;
        }
    }
}