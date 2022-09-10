#include "spirit_context.h"

#include "spirit_command_buffer.h"
#include "spirit_device.h"
<<<<<<< HEAD
#include "spirit_swapchain.h"
#include "spirit_material.h"
#include "spirit_fence.h"
=======
#include "spirit_fence.h"
#include "spirit_material.h"
#include "spirit_swapchain.h"
>>>>>>> devel

//
// Private functions
//

SpiritResult createSyncObjects(SpiritContext context);

void destroySyncObjects(SpiritContext context);

SpiritResult beginFrame(SpiritContext context, u32 *imageIndex);

SpiritResult endFrame(SpiritContext context, const u32 imageIndex);

<<<<<<< HEAD

=======
>>>>>>> devel
//
// Public functions
//

SpiritContext spCreateContext(SpiritContextCreateInfo *createInfo)
{

    SpiritContext context = new_var(struct t_SpiritContext);

    // initialize basic components
    // create window
    SpiritWindowCreateInfo windowCreateInfo = {};
<<<<<<< HEAD
    windowCreateInfo.windowSize = createInfo->windowSize;
    windowCreateInfo.title = createInfo->windowName;
    windowCreateInfo.fullscreen = createInfo->windowFullscreen;

    context->window = spCreateWindow (&windowCreateInfo);
=======
    windowCreateInfo.windowSize             = createInfo->windowSize;
    windowCreateInfo.title                  = createInfo->windowName;
    windowCreateInfo.fullscreen             = createInfo->windowFullscreen;

    context->window = spCreateWindow(&windowCreateInfo);
>>>>>>> devel
    if (!context->window)
    {
        log_fatal("Must have window to create context");
        spDestroyContext(context);
        return NULL;
    }
    context->screenResolution = spWindowGetPixelSize(context->window);
<<<<<<< HEAD
    context->windowSize = createInfo->windowSize;
=======
    context->windowSize       = createInfo->windowSize;
>>>>>>> devel
    db_assert(context->window);

    // create device
    SpiritDeviceCreateInfo deviceCreateInfo = {};
<<<<<<< HEAD
    deviceCreateInfo.enableValidation = createInfo->enableValidation;
    deviceCreateInfo.powerSaveMode = createInfo->powerSaving;

    deviceCreateInfo.appName = "";
    deviceCreateInfo.appVersion = VK_MAKE_VERSION(0, 0, 0);
    deviceCreateInfo.engineName = "Spirit Render";
    deviceCreateInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);

    deviceCreateInfo.windowExtensions = spWindowGetExtensions(context->window);
    deviceCreateInfo.window = context->window;

    const char *deviceExtensions[1] = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    deviceCreateInfo.requiredDeviceExtensions = deviceExtensions;
    deviceCreateInfo.requiredDeviceExtensionCount = 1;
    context->device = spCreateDevice (&deviceCreateInfo);
=======
    deviceCreateInfo.enableValidation       = createInfo->enableValidation;
    deviceCreateInfo.powerSaveMode          = createInfo->powerSaving;

    deviceCreateInfo.appName       = "";
    deviceCreateInfo.appVersion    = VK_MAKE_VERSION(0, 0, 0);
    deviceCreateInfo.engineName    = "Spirit Render";
    deviceCreateInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);

    deviceCreateInfo.windowExtensions = spWindowGetExtensions(context->window);
    deviceCreateInfo.window           = context->window;

    const char *deviceExtensions[] = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    deviceCreateInfo.requiredDeviceExtensions = deviceExtensions;
    deviceCreateInfo.requiredDeviceExtensionCount =
        array_length(deviceExtensions);

    const char *deviceLayers[] = {/* "VK_LAYER_LUNARG_assistant_layer", */
                                  "VK_LAYER_KHRONOS_validation"};
    deviceCreateInfo.requiredValidationLayers     = deviceLayers;
    deviceCreateInfo.requiredValidationLayerCount = array_length(deviceLayers);
    context->device = spCreateDevice(&deviceCreateInfo);
>>>>>>> devel
    if (!context->device)
    {
        log_fatal("Must have device to create context");
        spDestroyContext(context);
        return NULL;
    }

    // create swapchain
    SpiritSwapchainCreateInfo swapCreateInfo = {};
<<<<<<< HEAD
    context->windowSize = spWindowGetPixelSize(context->window);
    swapCreateInfo.windowRes = context->screenResolution;

    swapCreateInfo.selectedPresentMode = true;
    swapCreateInfo.preferredPresentMode = VK_PRESENT_MODE_FIFO_KHR;

    context->swapchain = spCreateSwapchain(&swapCreateInfo, context->device, NULL);
=======
    context->windowSize      = spWindowGetPixelSize(context->window);
    swapCreateInfo.windowRes = context->screenResolution;

    swapCreateInfo.selectedPresentMode  = true;
    swapCreateInfo.preferredPresentMode = VK_PRESENT_MODE_FIFO_KHR;

    context->swapchain =
        spCreateSwapchain(&swapCreateInfo, context->device, NULL);
>>>>>>> devel
    if (!context->swapchain)
    {
        log_fatal("Cannot create context without swapchain");
        spDestroyContext(context);
        return NULL;
    }

    // sync objects
    context->maxImagesInFlight = context->swapchain->imageCount - 1;
    if (createSyncObjects(context))
    {
        log_fatal("Failed to create sync objects");
        spDestroyContext(context);
        return NULL;
    }

    // create command buffers
    context->commandBufferCount = context->swapchain->imageCount;
<<<<<<< HEAD
    context->commandBuffers = new_array(
        SpiritCommandBuffer,
        context->commandBufferCount);

    for (u32 i = 0; i < context->commandBufferCount; ++i)
    {
        context->commandBuffers[i] = spCreateCommandBuffer(
            context->device, true);
=======
    context->commandBuffers =
        new_array(SpiritCommandBuffer, context->commandBufferCount);

    for (u32 i = 0; i < context->commandBufferCount; ++i)
    {
        context->commandBuffers[i] =
            spCreateCommandBuffer(context->device, true);
>>>>>>> devel
        if (context->commandBuffers[i] == NULL)
        {
            log_fatal("Failed to create command buffer");
            spDestroyContext(context);
            return NULL;
        }
    }

    LIST_INIT(&context->materials);

    context->currentFrame = 0;

    log_verbose("Created Context");

    return context;
}

SpiritResult spContextHandleWindowResized(SpiritContext context)
{
<<<<<<< HEAD
    if(!context && context->window) return SPIRIT_FAILURE;
=======
    if (!context && context->window)
        return SPIRIT_FAILURE;
>>>>>>> devel

    // recreate swapchain
    spDeviceWaitIdle(context->device);

    // update stored sizes
    context->screenResolution = spWindowGetPixelSize(context->window);
<<<<<<< HEAD
    context->windowSize = spWindowGetSize(context->window);

    // check swapchain exists, in case creation failed last frame
    SpiritSwapchainCreateInfo swapInfo = {};
    swapInfo.windowRes = context->screenResolution;

    context->swapchain = spCreateSwapchain(
        &swapInfo,
        context->device,
        context->swapchain);
=======
    context->windowSize       = spWindowGetSize(context->window);

    // check swapchain exists, in case creation failed last frame
    SpiritSwapchainCreateInfo swapInfo = {};
    swapInfo.windowRes                 = context->screenResolution;

    context->swapchain =
        spCreateSwapchain(&swapInfo, context->device, context->swapchain);
>>>>>>> devel

    if (!context->swapchain)
    {
        return SPIRIT_FAILURE;
    }

    // iterate through materials
    struct t_ContextMaterialListNode *np;
    LIST_FOREACH(np, &context->materials, data)
    {
        spMaterialUpdate(context, np->material);
    }

    return SPIRIT_SUCCESS;
<<<<<<< HEAD

=======
>>>>>>> devel
}

SpiritResult spContextSubmitFrame(SpiritContext context)
{
    // if failed to create swapchain last frame, try again now
    if (!context->swapchain)
    {
        if (spContextHandleWindowResized(context))
        {
            log_warning("Failed to handle window resize");
            return SPIRIT_FAILURE;
        }
    }

    u32 imageIndex;
    SpiritResult result;
    time_function_with_return(beginFrame(context, &imageIndex), result);
    if (result)
    {
        log_fatal("Error beginning frame");
        return SPIRIT_FAILURE;
    }

    // SpiritResolution winRes = spWindowGetPixelSize(context->window);
    // db_assert(
    //     context->screenResolution.w == winRes.w &&
    //     context->screenResolution.h == winRes.h);

    struct t_ContextMaterialListNode *np;
    LIST_FOREACH(np, &context->materials, data)
    {
        time_function_with_return(
            spMaterialRecordCommands(context, np->material, imageIndex),
            result);

        if (result)
        {
<<<<<<< HEAD
            log_error("Material %s failed to record commands", np->material->name);
=======
            log_error(
                "Material %s failed to record commands", np->material->name);
>>>>>>> devel
        }
    }

    time_function_with_return(endFrame(context, imageIndex), result);
    if (result)
    {
        log_fatal("Error ending frame");
        return SPIRIT_FAILURE;
    }

    return SPIRIT_SUCCESS;
}

SpiritWindowState spContextPollEvents(SpiritContext context)
{
    context->windowState = spWindowGetState(context->window);
    switch (context->windowState)
    {
    case SPIRIT_WINDOW_NORMAL:
        // TODO poll events
        return SPIRIT_WINDOW_NORMAL;
    case SPIRIT_WINDOW_RESIZING:
        spContextHandleWindowResized(context);
        return SPIRIT_WINDOW_RESIZING;
    case SPIRIT_WINDOW_MINIMIZED: return SPIRIT_WINDOW_MINIMIZED;
    case SPIRIT_WINDOW_CLOSED: return SPIRIT_WINDOW_CLOSED;
    default: return SPIRIT_WINDOW_NORMAL;
    }
}

inline SpiritWindowState spContextGetWindowState(const SpiritContext context)
{
    return context->windowState;
}

SpiritResult
spContextAddMaterial(SpiritContext context, const SpiritMaterial material)
>>>>>>> devel
{

    db_assert(context);
    db_assert(material);

    if (!context && material)
    {
        return SPIRIT_FAILURE;
    }

<<<<<<< HEAD
    // ensure the same material is not added twice
    // possibly should be added to release builds
    #ifdef DEBUG
=======
// ensure the same material is not added twice
// possibly should be added to release builds
#ifdef DEBUG
>>>>>>> devel
    struct t_ContextMaterialListNode *np;
    LIST_FOREACH(np, &context->materials, data)
    {
        if (np->material == material)
        {
<<<<<<< HEAD
            log_error("Same material added to context twice, address %p",
                material);
            return SPIRIT_FAILURE;
        }
    }
    #endif
=======
            log_error(
                "Same material added to context twice, address %p", material);
            return SPIRIT_FAILURE;
        }
    }
#endif
>>>>>>> devel

    struct t_ContextMaterialListNode *node =
        new_var(struct t_ContextMaterialListNode);

    node->material = material;

    LIST_INSERT_HEAD(&context->materials, node, data);

    ++context->materialCount;

    return SPIRIT_SUCCESS;
}

<<<<<<< HEAD
SpiritResult spContextRemoveMaterial(
    SpiritContext context,
    const SpiritMaterial material)
=======
SpiritResult
spContextRemoveMaterial(SpiritContext context, const SpiritMaterial material)
>>>>>>> devel
{

    struct t_ContextMaterialListNode *np;
    LIST_FOREACH(np, &context->materials, data)
    {
        if (np->material == material)
        {
            LIST_REMOVE(np, data);
            free(np);
            --context->materialCount;
            return SPIRIT_SUCCESS;
        }
    }

    return SPIRIT_FAILURE;
}

SpiritResult spDestroyContext(SpiritContext context)
{
    // destroy materials
    struct t_ContextMaterialListNode *np, *op;
    np = LIST_FIRST(&context->materials);
<<<<<<< HEAD
    while(!LIST_EMPTY(&context->materials))
=======
    while (!LIST_EMPTY(&context->materials))
>>>>>>> devel
    {
        op = np;
        np = LIST_NEXT(np, data);
        LIST_REMOVE(op, data);
        free(op);
    }

    destroySyncObjects(context);

<<<<<<< HEAD
    for (u32 i = 0; context->commandBuffers && i < context->commandBufferCount; ++i)
=======
    for (u32 i = 0; context->commandBuffers && i < context->commandBufferCount;
         ++i)
>>>>>>> devel
    {
        SpiritCommandBuffer buf = context->commandBuffers[i];
        if (buf)
        {
            if (buf->state == SPIRIT_COMMAND_BUFFER_STATE_BUSY)
                spCommandBufferWait(context->device, buf, UINT32_MAX);
            else if (buf->state == SPIRIT_COMMAND_BUFFER_STATE_RECORDING)
                spCommandBufferEnd(buf);

            spDestroyCommandBuffer(context->device, buf);
        }
    }

<<<<<<< HEAD
    context->swapchain && spDestroySwapchain(context->swapchain, context->device);
    context->device && spDestroyDevice(context->device);
    context->window && spDestroyWindow (context->window);
=======
    context->swapchain &&spDestroySwapchain(
        context->swapchain, context->device);
    context->device &&spDestroyDevice(context->device);
    context->window &&spDestroyWindow(context->window);
>>>>>>> devel

    free(context->commandBuffers);

    free(context);

    return SPIRIT_SUCCESS;
}

//
// Helpers
//

SpiritResult beginFrame(SpiritContext context, u32 *imageIndex)
{

    // aquire image
    if (spSwapchainAquireNextImage(
<<<<<<< HEAD
        context->device,
        context->swapchain,
        context->imageAvailableSemaphores[context->currentFrame],
        imageIndex)) return SPIRIT_FAILURE;

    // if the imageInFlight fence is not null, wait for it to complete
    if (spCommandBufferWait(
        context->device,
        context->commandBuffers[*imageIndex],
        UINT64_MAX)) return SPIRIT_FAILURE;

=======
            context->device,
            context->swapchain,
            context->imageAvailableSemaphores[context->currentFrame],
            imageIndex))
        return SPIRIT_FAILURE;

    // if the imageInFlight fence is not null, wait for it to complete
    if (spCommandBufferWait(
            context->device, context->commandBuffers[*imageIndex], UINT64_MAX))
        return SPIRIT_FAILURE;
>>>>>>> devel

    SpiritCommandBuffer buf = context->commandBuffers[*imageIndex];

    spCommandBufferBegin(buf);

    // Dynamic state
    VkViewport viewport = {
<<<<<<< HEAD
        .x = 0.0f,
        .y = (f32) context->screenResolution.h,
        .width = (f32) context->screenResolution.w,
        .height = -(f32) context->screenResolution.h,
        .minDepth = 0.0f,
        .maxDepth = 1.0f
    };

    VkRect2D scissor = {
        .offset.x = scissor.offset.y = 0,
        .extent.width = context->screenResolution.w,
        .extent.height = context->screenResolution.h
    };
=======
        .x        = 0.0f,
        .y        = (f32)context->screenResolution.h,
        .width    = (f32)context->screenResolution.w,
        .height   = -(f32)context->screenResolution.h,
        .minDepth = 0.0f,
        .maxDepth = 1.0f};

    VkRect2D scissor = {
        .offset.x = scissor.offset.y = 0,
        .extent.width                = context->screenResolution.w,
        .extent.height               = context->screenResolution.h};
>>>>>>> devel

    vkCmdSetViewport(buf->handle, 0, 1, &viewport);
    vkCmdSetScissor(buf->handle, 0, 1, &scissor);

    return SPIRIT_SUCCESS;
<<<<<<< HEAD

=======
>>>>>>> devel
}

SpiritResult endFrame(SpiritContext context, const u32 imageIndex)
{

    SpiritCommandBuffer buf = context->commandBuffers[imageIndex];
<<<<<<< HEAD
    const u32 currentFrame = context->currentFrame;
=======
    const u32 currentFrame  = context->currentFrame;
>>>>>>> devel

    spCommandBufferEnd(buf);

    VkPipelineStageFlags waitStages =
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

    // submit command buffer
    if (spCommandBufferSubmit(
<<<<<<< HEAD
        context->device,
        buf,
        context->imageAvailableSemaphores[currentFrame],
        context->queueCompleteSemaphores[currentFrame],
        &waitStages))
    {
        log_fatal("Failed to submit command buffer");
       return SPIRIT_FAILURE;
=======
            context->device,
            buf,
            context->imageAvailableSemaphores[currentFrame],
            context->queueCompleteSemaphores[currentFrame],
            &waitStages))
    {
        log_fatal("Failed to submit command buffer");
        return SPIRIT_FAILURE;
>>>>>>> devel
    }

    // present image
    if (spSwapchainPresent(
            context->device,
            context->swapchain,
            context->queueCompleteSemaphores[currentFrame],
            imageIndex))
    {
        log_error("Failed to present image");
        return SPIRIT_FAILURE;
    };

    // increment current image
    context->currentFrame = (currentFrame + 1) % context->maxImagesInFlight;

    return SPIRIT_SUCCESS;
}

SpiritResult createSyncObjects(SpiritContext context)
{

    db_assert_msg(context->swapchain, "Context must have swapchain");

    const u32 imagesInFlight = context->maxImagesInFlight;
<<<<<<< HEAD
    db_assert_msg(imagesInFlight < 10, "Images in flight should not be more then 10")
    const u32 imageCount = context->swapchain->imageCount;
    db_assert_msg(imageCount < 11, "Image count should not be more then 10");
    db_assert_msg(imagesInFlight == imageCount - 1,
        "Images in flight should be imageCount - 1");

    context->imageAvailableSemaphores = new_array(VkSemaphore, imagesInFlight);
    context->queueCompleteSemaphores = new_array(VkSemaphore, imagesInFlight);
=======
    db_assert_msg(
        imagesInFlight < 10, "Images in flight should not be more then 10")
        const u32 imageCount = context->swapchain->imageCount;
    db_assert_msg(imageCount < 11, "Image count should not be more then 10");
    db_assert_msg(
        imagesInFlight == imageCount - 1,
        "Images in flight should be imageCount - 1");

    context->imageAvailableSemaphores = new_array(VkSemaphore, imagesInFlight);
    context->queueCompleteSemaphores  = new_array(VkSemaphore, imagesInFlight);
>>>>>>> devel

    VkSemaphoreCreateInfo semaphoreInfo = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .flags = 0,
<<<<<<< HEAD
        .pNext = 0
    };

    for (size_t i = 0; i < imagesInFlight; i++) {

        bool failure = false;
        if (vkCreateSemaphore(
            context->device->device,
            &semaphoreInfo,
            NULL,
            &context->imageAvailableSemaphores[i])) failure = true;
       if (vkCreateSemaphore(
            context->device->device,
            &semaphoreInfo,
            NULL,
            &context->queueCompleteSemaphores[i])) failure = true;
=======
        .pNext = 0};

    for (size_t i = 0; i < imagesInFlight; i++)
    {

        bool failure = false;
        if (vkCreateSemaphore(
                context->device->device,
                &semaphoreInfo,
                NULL,
                &context->imageAvailableSemaphores[i]))
            failure = true;
        if (vkCreateSemaphore(
                context->device->device,
                &semaphoreInfo,
                NULL,
                &context->queueCompleteSemaphores[i]))
            failure = true;
>>>>>>> devel

        if (failure)
        {
            log_error("Failed to create syncronization objects");
            return SPIRIT_FAILURE;
        }
    }

    return SPIRIT_SUCCESS;
}

void destroySyncObjects(SpiritContext context)
{
    for (u32 i = 0; i < context->maxImagesInFlight; i++)
    {
<<<<<<< HEAD
        if (context->queueCompleteSemaphores && context->queueCompleteSemaphores[i])
            vkDestroySemaphore(context->device->device,
                context->queueCompleteSemaphores[i],
                ALLOCATION_CALLBACK);
        if (context->imageAvailableSemaphores && context->imageAvailableSemaphores[i])
            vkDestroySemaphore(context->device->device,
=======
        if (context->queueCompleteSemaphores &&
            context->queueCompleteSemaphores[i])
            vkDestroySemaphore(
                context->device->device,
                context->queueCompleteSemaphores[i],
                ALLOCATION_CALLBACK);
        if (context->imageAvailableSemaphores &&
            context->imageAvailableSemaphores[i])
            vkDestroySemaphore(
                context->device->device,
>>>>>>> devel
                context->imageAvailableSemaphores[i],
                NULL);
    }

<<<<<<< HEAD
    if (context->imageAvailableSemaphores) free(context->imageAvailableSemaphores);
    if (context->queueCompleteSemaphores)  free(context->queueCompleteSemaphores);
=======
    if (context->imageAvailableSemaphores)
        free(context->imageAvailableSemaphores);
    if (context->queueCompleteSemaphores)
        free(context->queueCompleteSemaphores);
>>>>>>> devel
}
