//
//  YOLayout.h
//  YOLayout
//
//  Created by Gabriel Handford on 10/29/13.
//  Copyright (c) 2014 YOLayout. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

#define YOWeakObject(o) __typeof__(o) __weak
#define YOSelf YOWeakObject(self)

typedef enum {
  // SIZING
  //! Size the view to fit vertically
  YOLayoutOptionsSizeToFitVertical = 1 << 0,
  //! Size the view to fit horizontally
  YOLayoutOptionsSizeToFitHorizontal = 1 << 1,
  //! Size the view to fit both horizontally and vertically
  YOLayoutOptionsSizeToFit = YOLayoutOptionsSizeToFitVertical | YOLayoutOptionsSizeToFitHorizontal,

  /*!
   Constrain sizeThatFit's width to the passed in frame.

   For example, UILabel sizeThatFits: may return a larger width than was specified, and this will constrain it.
   */
  YOLayoutOptionsConstrainWidth = 1 << 2,
  //! Constrain sizeThatFit's height to the passed in frame
  YOLayoutOptionsConstrainHeight = 1 << 3,
  //! Constrain sizeThatFit's height and width
  YOLayoutOptionsConstrainSize = YOLayoutOptionsConstrainWidth | YOLayoutOptionsConstrainHeight,

  /*!
   Constrain sizeThatFits to the size specified but maintain the original aspect ratio.

   This is useful for an image view that may need to be constrained to a max size, but still maintain its aspect ratio.
   */
  YOLayoutOptionsConstrainSizeMaintainAspectRatio = 1 << 4,

  //! Whether the height specified is the default. Using this option will use the specified height when sizeThatFits: returns a 0 height.
  YOLayoutOptionsDefaultHeight = 1 << 5,
  //! Whether the width specified is the default. Using this option will use the specified width when sizeThatFits: returns a 0 width.
  YOLayoutOptionsDefaultWidth = 1 << 6,
  /*!
   Whether the size specified is the default. Using this option will use the specified width and/or height when sizeThatFits: returns a 0 width and/or height, respectively.

   This is useful for an image view that has to load its data and may initially return 0 for sizeThatFits.
   */
  YOLayoutOptionsDefaultSize = YOLayoutOptionsDefaultHeight | YOLayoutOptionsDefaultWidth,

  // ALIGNMENT
  //! After sizing, center vertically in the passed in rect
  YOLayoutOptionsAlignCenterVertical = 1 << 10,
  //! After sizing, center horizontally in the passed in rect
  YOLayoutOptionsAlignCenterHorizontal = 1 << 11,
  //! After sizing, center vertically and horizontally in the passed in rect
  YOLayoutOptionsAlignCenter = YOLayoutOptionsAlignCenterVertical | YOLayoutOptionsAlignCenterHorizontal,
  //! After sizing, aligns the view with the right of the passed in rect
  YOLayoutOptionsAlignRight = 1 << 12,
  //! After sizing, aligns the view with the bottom of the passed in rect
  YOLayoutOptionsAlignBottom = 1 << 13,
} YOLayoutOptions;


@protocol YOLayout <NSObject>

/*!
 Layout the subviews.
 
 @param size Size to layout in
 */
- (CGSize)layoutSubviews:(CGSize)size;

/*!
 Size that fits.
 
 @param size Size to layout in; Should have a width specified.
 @result The size needed to display the view
 */
- (CGSize)sizeThatFits:(CGSize)size;

/*!
 Set frame for the (sub)view.
 If we are calculating sizeThatFits, this doesn't actually set the views frame.
 
 @param frame Frame
 @param view View should conform to YOLView informal protocol.
 */
- (CGRect)setFrame:(CGRect)frame view:(id)view;

/*!
 Set frame for the (sub)view.
 If we are calculating sizeThatFits, this doesn't actually set the views frame.
 
 @param frame Frame
 @param view View should conform to YOLView informal protocol.
 @param needsLayout If YES, calls setNeedsLayout on view.
 */
- (CGRect)setFrame:(CGRect)frame view:(id)view needsLayout:(BOOL)needsLayout;

/*!
 Set the (sub)view frame, then size to fit the view vertically.
 If we are calculating sizeThatFits, this doesn't actually set the views frame.
 Use this value instead of view.frame since the views frame might not have been set.
 
 @param frame Frame
 @param view View should conform to YOLView informal protocol.
 @result The view frame.
 */
- (CGRect)sizeToFitVerticalInFrame:(CGRect)frame view:(id)view;

/*!
 Set the (sub)view frame.
 If we are calculating sizeThatFits, this doesn't actually set the views frame.
 Use this value instead of view.frame since the views frame might not have been set.
 
 @param frame Frame
 @param view View should conform to YOLView informal protocol.
 @param options Options for setFrame; See YOLayoutOptions for more info
 @result The view frame.
 */
- (CGRect)setFrame:(CGRect)frame view:(id)view options:(YOLayoutOptions)options;

/*!
 Center view with size in frame.
 
 @param size Desired size
 @param frame In frame
 @param view View
 @result The view frame.
 */
- (CGRect)centerWithSize:(CGSize)size frame:(CGRect)frame view:(id)view;

/*!
 Set the (sub)view frame.
 If we are calculating sizeThatFits, this doesn't actually set the views frame.
 Use this value instead of view.frame since the views frame might not have been set.
 
 @param frame Frame
 @param inRect Rect to optionally position in for YOLayoutOptionsCenter, YOLayoutOptionsCenterVertical, YOLayoutOptionsRightAlign, etc.
 @param view View
 @param options Options for setFrame; See YOLayoutOptions for more info
 @result The view frame.
 */
- (CGRect)setFrame:(CGRect)frame inRect:(CGRect)inRect view:(id)view options:(YOLayoutOptions)options;

/*!
 Set the (sub)view frame.
 Calls sizeThatFits on the view and then centers it. If inRect.height == 0, we only center horizontally.
 @param inRect The containing rectangle.
 @param view View
 */
- (CGRect)setFrameInRect:(CGRect)inRect view:(id)view;

/*!
 Set origin.
 */
- (CGRect)setOrigin:(CGPoint)origin view:(id)view;
- (CGRect)setOrigin:(CGPoint)origin view:(id)view sizeToFit:(BOOL)sizeToFit;

/*!
 Set size.
 */
- (CGRect)setSize:(CGSize)size view:(id)view;
- (CGRect)setSize:(CGSize)size view:(id)view sizeToFit:(BOOL)sizeToFit;

/*!
 Set origin, x position.
 Use this value instead of view.frame since the views frame might not have been set.
 
 @param x X position
 @param frame Frame
 @param view View should conform to YOLView informal protocol.
 @result The view frame.
 */
- (CGRect)setX:(CGFloat)x frame:(CGRect)frame view:(id)view;

/*!
 Set origin, y position.
 
 Use this value instead of view.frame since the views frame might not have been set.
 
 @param y Y position
 @param frame Frame
 @param view View should conform to YOLView informal protocol.
 @result The view frame.
 */
- (CGRect)setY:(CGFloat)y frame:(CGRect)frame view:(id)view;

/*!
 @deprecated Use setY:frame:view:
 */
- (CGRect)setY:(CGFloat)y view:(id)view;

/*!
 If layout is required. Otherwise cached value may be returned.
 This should be called when a views data changes.
 */
- (void)setNeedsLayout;

/*!
 For subclasses, in rare cases, if they need to know whether the layout will
 be applied or not via setFrame:view:
 
 @result YES if we are only sizing, NO if we are setting frames
 */
- (BOOL)isSizing;

@end


/*
 UIViews can implement this protocol, to enable custom layouts.
 */
@protocol YOLayoutView <NSObject>

/*!
 Layout object belonging to the class implementing this protocol.
 */
@property id <YOLayout>layout;

@end


/*!
 UIViews can also use custom layouts even if they aren't in the view hierarchy (can't do that with Auto Layout!). This protocol presents a convention for how to create drawable views. To create a drawable view, simply create a YOView that implements drawInRect:. Then superviews can draw the view in their drawRect method.
 */
@protocol YODrawableView <YOLayoutView>

/*!
 @result Draw the drawable
 */
- (void)drawInRect:(CGRect)rect;

@end


/*!
 Block containing logic to layout or size the current view, with the specified
 size as a hint. Return the size used.

 You should never setFrame on subviews in this block. Instead use the methods
 in layout in order to setFrame, and use what those methods return to layout other
 subviews. This is because setFrame calls are no-ops when the view is only sizing.

 This block must be implemented.

 @param layout Layout
 @param size Size to layout in
 @result size Size of the view being laid out
 */
typedef CGSize (^YOLayoutBlock)(id<YOLayout> layout, CGSize size);


/*!
 YOLayout is a way to size and layout views without having to implement layoutSubview and
 sizeToFit separately.
 
 It also provides a basic cache to avoid layout when the view is unchanged.
 
 YOLayout calculates a size that best fits the receiver’s subviews,
 without altering the subviews frames, or affecting layoutSubviews call hierarchy.
 
 Instead of defining both sizeThatFits: and layoutSubviews, you create a block named layoutBlock.
 In this block you use the layout instance to set the subview frames (if sizing).

 This prevents your code from altering subviews when you are sizing (for sizeThatFits:).
 
 For example,
 
 CGRect titleLabelFrame = [layout setFrame:CGRectMake(x, y, 400, 0) view:_titleLabel options:YOLayoutOptionsSizeToFit];
 // titleLabelFrame may have a different width and will have a valid height
 
 You can combine YOLayoutOptionsSizeToFit and YOLayoutOptionsCenter to have it be centered with a variable height.
 For example,
 
 CGRect titleLabelFrame = [layout setFrame:CGRectMake(x, y, 400, 0) view:_titleLabel options:YOLayoutOptionsSizeToFit|YOLayoutOptionsCenter];
 // titleLabelFrame may have a different width and will have a valid height and will have an x position so it is centered
 
 You can also combine YOLayoutOptionsSizeToFit with YOLayoutOptionsConstraintWidth
 to make sure the width isn't set larger than expected. For example,
 
 CGRect titleLabelFrame = [layout setFrame:CGRectMake(x, y, 400, 0) view:_titleLabel options:YOLayoutOptionsSizeToFit|YOLayoutOptionsConstraintWidth];
 // titleLabelFrame may have a different width but it won't be larger than 400
 
 You can combine YOLayoutOptionsSizeToFit, YOLayoutOptionsConstraintWidth, and YOLayoutOptionsDefaultWidth to make sure
 a view sizes to fit with max and default width (when 0).
 */
@interface YOLayout : NSObject <YOLayout>

@property (readonly, getter=isSizing) BOOL sizing;
//! Block containing logic to layout or size the current view. See the discussion above the YOLayoutBlock typedef for more info.
@property (copy) YOLayoutBlock layoutBlock;

/*!
 Set a custon/fixed size that fits.
 Override the size that is returned by sizeThatFits:(CGSize)size.
 Defaults to CGSizeZero, which is unset.
 If height is not set (is 0), then we will use this size value for sizeThatFits:.
 */
@property CGSize sizeThatFits;

/*!
 Create layout.

 @param layoutBlock Block containing layout code. See the discussion above the YOLayoutBlock typedef for more info.
 */
- (id)initWithLayoutBlock:(YOLayoutBlock)layoutBlock;

/*!
 Default layout.

 @param view View for layout (weak reference).
 @param layoutBlock Block containing layout code. See the discussion above the YOLayoutBlock typedef for more info.
 @result Layout
 */
+ (YOLayout *)layoutWithLayoutBlock:(YOLayoutBlock)layoutBlock;

#pragma mark Common Layouts

/*!
  A layout which lays out subviews from top to bottom using sizeToFitVerticalInFrame:.

  @param view
  @param Layout
 */
+ (YOLayout *)vertical:(id)view;

/*!
 A layout which makes the subview the full size passed in.

 @param view
 @param Layout
 */
+ (YOLayout *)fill:(id)view;

/*!
 A layout block which lays out subviews from top to bottom using sizeToFitVerticalInFrame:.

 @param view
 @param Layout block
 */
+ (YOLayoutBlock)verticalLayout:(id)view;

/*!
 A layout block which lays out subviews from top to bottom using sizeToFitVerticalInFrame:.

 @param view
 @param Layout block
 */
+ (YOLayoutBlock)fillLayout:(id)view;

@end
