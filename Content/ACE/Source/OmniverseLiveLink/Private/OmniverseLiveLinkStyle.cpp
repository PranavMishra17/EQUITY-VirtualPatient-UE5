// Copyright(c) 2022-2023, NVIDIA CORPORATION. All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#include "OmniverseLiveLinkStyle.h"
#include "OmniverseLiveLink.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr< FSlateStyleSet > FOmniverseLiveLinkStyle::StyleInstance = NULL;

void FOmniverseLiveLinkStyle::Initialize()
{
    if( !StyleInstance.IsValid() )
    {
        StyleInstance = Create();
        FSlateStyleRegistry::RegisterSlateStyle( *StyleInstance );
    }
}

void FOmniverseLiveLinkStyle::Shutdown()
{
    FSlateStyleRegistry::UnRegisterSlateStyle( *StyleInstance );
    ensure( StyleInstance.IsUnique() );
    StyleInstance.Reset();
}

FName FOmniverseLiveLinkStyle::GetStyleSetName()
{
    static FName StyleSetName( TEXT( "OmniverseLiveLinkStyle" ) );
    return StyleSetName;
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )

const FVector2D Icon16x16( 16.0f, 16.0f );
const FVector2D Icon20x20( 20.0f, 20.0f );
const FVector2D Icon48x48( 48.0f, 48.0f );

TSharedRef< FSlateStyleSet > FOmniverseLiveLinkStyle::Create()
{
    TSharedRef< FSlateStyleSet > Style = MakeShareable( new FSlateStyleSet( "OmniverseLiveLinkStyle" ) );
    Style->SetContentRoot( IPluginManager::Get().FindPlugin( "OmniverseLiveLink" )->GetBaseDir() / TEXT( "Resources" ) );

    Style->Set( "OmniverseLiveLink.PluginAction", new IMAGE_BRUSH( TEXT( "nvidia-omniverse-button-icon-48x48" ), Icon48x48 ) );

    return Style;
}

#undef IMAGE_BRUSH

void FOmniverseLiveLinkStyle::ReloadTextures()
{
    if( FSlateApplication::IsInitialized() )
    {
        FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
    }
}

const ISlateStyle& FOmniverseLiveLinkStyle::Get()
{
    return *StyleInstance;
}
